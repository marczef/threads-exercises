#pragma once

#include <functional>
#include <chrono>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace threads_exercise {

/*
inmemory scheduler:
= schedule to run task at specific time
= schedule recurring tasks
= cancel scheduled task
= query the next exectuon time
= execute jobs on worker pool
*/

class Scheduler {
public:
    using TaskKey = std::string;
    using Task = std::function<void()>;

    Scheduler(size_t numWorkers);
    ~Scheduler();

    void schedule(Task&& task);

private:
    std::vector<std::thread> workers;
    std::mutex m;
    std::condition_variable cv;
    std::queue<std::unique_ptr<Task>> taskQueue;
    bool currRunning = true;

    void worker();
};

} // threads_exercise