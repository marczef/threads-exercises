#include "Scheduler.h"

namespace threads_exercise {

Scheduler::Scheduler(size_t numWorkers) {
    
    for(int i{0}; i < numWorkers; i++) {
        workers.push_back(std::thread(&Scheduler::worker, this));
    }
}

void Scheduler::schedule(Task&& task) {
    std::unique_lock<std::mutex> lock(m);
    taskQueue.push(std::make_unique<Task>(std::move(task)));
    cv.notify_one();
}

void Scheduler::worker() {

    while(true) {

        std::unique_ptr<Scheduler::Task> currTask;

        {
            std::unique_lock<std::mutex> lock(m);

            cv.wait(lock, [this]{ return !taskQueue.empty() || !currRunning; });

            if(taskQueue.empty() && !currRunning) return;

            currTask = std::move(taskQueue.front());
            taskQueue.pop();
        }

        (*currTask)();
    }
}

Scheduler::~Scheduler() {
    {
        std::unique_lock<std::mutex> lock(m);
        currRunning = false;
        cv.notify_all();
    }
    
    for(size_t i{0}; i < workers.size(); i++) {
        workers[i].join();
    }
}


} // threads_exercise