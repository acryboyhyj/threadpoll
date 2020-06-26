#ifndef __THREADPOLL_H__
#define __THREADPOLL_H__
#include <memory>
#include <functional>
#include "PollCore.h"

class ThreadPoll
{
public:
    using Task = std::function<void()>;

    ThreadPoll(size_t initThreads = 0);
    ~ThreadPoll();

    void start();
    void shutdown();

    void schedule(Task &f);

private:
    std::shared_ptr<PollCore> m_core;
};

#endif // __THREADPOLL_H__