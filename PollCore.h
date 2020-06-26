#ifndef __POLLCORE_H__
#define __POLLCORE_H__
#include <memory>
#include <vector>
#include <functional>
#include <mutex>
#include <atomic>

class WorkerThread;
class PollScheduler;

class PollCore : public std::enable_shared_from_this<PollCore>
{
public:
    using workerPtr = std::unique_ptr<WorkerThread>;
    using Task = std::function<void()>;

public:
    PollCore(int initThreads);
    ~PollCore();

    void start();

    void schedule(const Task &task);
    bool excuteTask();

    void shutdown();

private:
    void run();

private:
    size_t m_threadNums;
    std::unique_ptr<PollScheduler> m_scheduler;

    std::vector<workerPtr> m_workers;
    std::mutex m_taskmutex;
    std::atomic<bool> m_running;
};
#endif // __POLLCORE_H__