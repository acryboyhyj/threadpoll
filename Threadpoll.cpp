#include "Threadpoll.h"

ThreadPoll::ThreadPoll(size_t initThreads) : m_core(new PollCore(initThreads))
{
}

ThreadPoll::~ThreadPoll()
{
}

void ThreadPoll::start()
{
    m_core->start();
}

void ThreadPoll::shutdown()
{
    m_core->shutdown();
}

void ThreadPoll::schedule(Task &f)
{
    m_core->schedule(f);
}