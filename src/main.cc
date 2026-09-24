#include "ProducerConsumer.h"
#include "Scheduler.h"
#include <iostream>

int main() {
    threads_exercise::Scheduler scheduler(3);

    scheduler.schedule([] {
        std::cout << "first function started " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "first function ended " << std::endl;
    });

    scheduler.schedule([] {
        std::cout << "second function started " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "second function ended " << std::endl;
    });

    scheduler.schedule([] {
        std::cout << "third function started " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "third function ended " << std::endl;
    });

    scheduler.schedule([] {
        std::cout << "fourth function started " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "fourth function ended " << std::endl;
    });
}