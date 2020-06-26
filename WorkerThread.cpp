
#include "WorkerThread.h"
#include <unistd.h>
#include "PollCore.h"
#include "muduo/base/Logging.h"
#include "muduo/base/CurrentThread.h"
WorkerThread &WorkerThread::operator=(WorkerThread &&rhs)
{
    if (&rhs != this)
    {
        m_poll = std::move(rhs.m_poll);
        rhs.m_poll = nullptr;
        m_threadptr = std::move(rhs.m_threadptr);
        rhs.m_threadptr = nullptr;
    }

    return *this;
}

WorkerThread::WorkerThread(WorkerThread &&rhs)
{
    if (&rhs != this)
    {
        m_poll = std::move(rhs.m_poll);
        rhs.m_poll = nullptr;
        m_threadptr = std::move(rhs.m_threadptr);
        rhs.m_threadptr = nullptr;
    }
}

void WorkerThread::run()
{

    while (m_running)
    {
        if (!m_poll->excuteTask())
        {
            return;
        }
    }
    LOG_WARN << muduo::CurrentThread::tid() << "exit";
}

void WorkerThread::stop()
{
    m_running = false;
}

void WorkerThread::join()
{
    m_threadptr->join();
}
WorkerThread::WorkerThread(std::shared_ptr<PollCore> &poll) : m_poll(poll),
                                                              m_threadptr(new std::thread(std::bind(&WorkerThread::run, this))),
                                                              m_running(true)
{
    assert(m_poll != nullptr);
}

WorkerThread::~WorkerThread()
{
}