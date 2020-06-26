#include "PollScheduler.h"
#include "muduo/base/CurrentThread.h"
#include "muduo/base/Logging.h"
PollScheduler::PollScheduler() : m_running(true)
{
}

PollScheduler::~PollScheduler()
{
}

void PollScheduler::push(const Task &task)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_container.push(task);
    m_notEmpty.notify_one();
}

PollScheduler::Task PollScheduler::pop()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_notEmpty.wait(lock, [this]() {
        return !this->m_container.empty() || !m_running;
    });
    if (m_running)
    {
        Task task = m_container.front();
        m_container.pop();
        return task;
    }
    else
    {
        LOG_WARN << "scheduiler stop task";
        return nullptr;
    }
}

bool PollScheduler::empty()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_container.empty();
}

void PollScheduler::start()
{
    if (!m_running)
    {
        m_running = true;
    }
}
void PollScheduler::stop()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_container.clear();
    }
    m_running.store(false, std::memory_order_seq_cst);
    m_notEmpty.notify_all();
}