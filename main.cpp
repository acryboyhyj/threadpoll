#include "Threadpoll.h"
#include <unistd.h>
#include <functional>
#include <iostream>

void first_task()
{

    std::cout << "first task is running\n";
    sleep(6);
    std::cout << "first task is running done\n";
}

void second_task()
{
    std::cout << "second task is running\n";
    sleep(7);
    std::cout << "second task is running done\n";
}

int main(int argc, char *argv[])
{
    // Create fifo thread pool container with two threads.
    ThreadPoll tp(2);

    // Add some tasks to the pool.
    ThreadPoll::Task funca = std::bind(&first_task);
    tp.schedule(funca);
    ThreadPoll::Task funb = std::bind(&second_task);

    tp.schedule(funb);
    tp.schedule(funca);
    tp.start();

    //  Wait until all tasks are finished.
    // tp.wait();
    sleep(1);

    int count = 0;
    while (count > 1)
    {
        sleep(1);
        count++;
    }

    tp.shutdown();
    while (count > 6)
    {
        sleep(1);
        count++;
    }
    tp.start();
    while (1)
    {
        sleep(1);
    }
    // Now all tasks are finished!
    return 0;
}
