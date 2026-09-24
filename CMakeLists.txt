cmake_minimum_required(VERSION 3.10)
project(threads_exercises)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

add_executable(main
	src/main.cc
	src/ProducerConsumer.cc
	src/Scheduler.cc
)

find_package(Threads REQUIRED)
target_link_libraries(main PRIVATE Threads::Threads)