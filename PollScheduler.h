#ifndef __POLLSHCEDULER_H__
#define __POLLSHCEDULER_H__
#include <functional>
#include <queue>
#include <condition_variable>
#include <atomic>

class PollScheduler
{
public:
    // using Task = std::function<void()>;
    typedef std::function<void()> Task;

public:
    PollScheduler();
    ~PollScheduler();
    void push(const Task &task);

    Task pop();
    bool empty();

    void start();
    void stop();

private:
    std::queue<Task> m_container;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::atomic<bool> m_running;
};
#endif // __POLLSHCEDULER_H__