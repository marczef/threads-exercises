#include <iostream>
#include <thread>
#include <chrono>

#include "ProducerConsumer.h"

namespace threads_exercise {

ProducerConsumer::ProducerConsumer(int num, std::size_t max_size, int time_produced, int time_consumed) : num(num), buffer(max_size) {

    std::thread producer_thread(&ProducerConsumer::producer, this, time_produced);
    std::thread consumer_thread(&ProducerConsumer::consumer, this, time_consumed);

    producer_thread.join();
    consumer_thread.join();
}

void ProducerConsumer::producer(int time) {
    while (true) {

        int val;

        {
            std::unique_lock<std::mutex> lock(m);

            cv.wait(lock, [this]{ return buffer.q.size() < buffer.max_size; });
            std::cout << " PRODUCER started producing : " << std::endl;
            val = curr_num; 
        }
        

        std::this_thread::sleep_for(std::chrono::seconds(time));

        {
            std::unique_lock<std::mutex> lock(m);
            buffer.q.push(curr_num++); 
            std::cout << " PRODUCER produced item nr : " << val << std::endl;
            cv.notify_all();

            if(curr_num == num) return;
        }
    }

}

void ProducerConsumer::consumer(int time) {
    while (true) {

        int val;

        {
            std::unique_lock<std::mutex> lock(m); 

            if(curr_num == num && buffer.q.empty()) return; 
            cv.wait(lock, [this]{ return !buffer.q.empty(); });

            val = buffer.q.front();
            std::cout << "  CONSUMER started consuming : " << std::endl;
            buffer.q.pop();
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(time));
        std::cout << "  CONSUMER consumed item nr : " << val << std::endl;
        cv.notify_all();

    }
}

} //namespace threads_exercise