#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__
#include <thread>
#include <memory.h>
#include <atomic>
#include <assert.h>
#include <functional>
class PollCore;
class WorkerThread
{
public:
    WorkerThread(std::shared_ptr<PollCore> &poll);
    ~WorkerThread();

    WorkerThread &operator=(const WorkerThread &rhs) = delete;
    WorkerThread(const WorkerThread &rhs) = delete;

    WorkerThread &operator=(WorkerThread &&rhs);
    WorkerThread(WorkerThread &&rhs);

    void run();
    void stop();
    void join();

private:
    std::shared_ptr<PollCore> m_poll;
    std::unique_ptr<std::thread> m_threadptr;
    std::atomic<bool> m_running;
};

#endif // __WORKERTHREAD_H__