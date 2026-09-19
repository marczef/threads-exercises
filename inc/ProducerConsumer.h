#pragma once 

#include <mutex>
#include <condition_variable>
#include <queue>

namespace threads_exercise {

class ProducerConsumer {
    public: 

    ProducerConsumer(int num, std::size_t max_size, int time_produced, int time_consumed);

    void producer(int time);
    void consumer(int time);

    private:
    
    std::mutex m;
    int curr_num = 0;
    std::condition_variable cv;
    int num;

    struct Buffer {
        Buffer(std::size_t m_size) : max_size(m_size) {}
        std::size_t max_size;
        std::queue<int> q;
    };

    Buffer buffer;

};

} //namespace threads_exercise