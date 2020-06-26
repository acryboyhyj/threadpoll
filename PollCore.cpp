
#include "PollCore.h"
#include <utility>
#include "PollScheduler.h"
#include "WorkerThread.h"
#include "muduo/base/Logging.h"
#include <iostream>
PollCore::PollCore(int initThreads) : m_threadNums(initThreads), m_scheduler(new PollScheduler()), m_running(false)

{
}

PollCore::~PollCore()
{
    if (m_running)
    {
        shutdown();
    }
}

void PollCore::start()
{
    if (!m_running)
    {
        m_workers.resize(m_threadNums);
        for (auto &workerPtr : m_workers)
        {
            std::shared_ptr<PollCore> guradThis(shared_from_this());
            workerPtr.reset(new WorkerThread(guradThis));
        }
        m_running = true;
        m_scheduler->start();
    }
}

void PollCore::schedule(const Task &task)
{
    m_scheduler->push(task);
}

bool PollCore::excuteTask()
{
    Task task = m_scheduler->pop();
    if (task)
    {
        task();
        return true;
    }
    else
    {
        return false;
    }
}

void PollCore::shutdown()
{
    if (m_running)
    {
        m_running = false;
        m_scheduler->stop();
        for (auto &thread : m_workers)
        {
            thread->stop();
            thread->join();
        }
        m_workers.clear();
    }
}
