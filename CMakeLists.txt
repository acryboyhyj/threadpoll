cmake_minimum_required(VERSION 3.5)

project(ThreadPoll)
add_definitions(-std=c++11 -g -Wall)
include_directories(${PROJECT_SOURCE_DIR})
set(SrcList
    main.cpp 
    Threadpoll.cpp
    PollCore.cpp 
    PollScheduler.cpp
    WorkerThread.cpp
)
add_executable(ThreadPoll ${SrcList})
link_directories(/usr/lib/muduo)
target_link_libraries(ThreadPoll 
                        muduo_base
                        pthread)