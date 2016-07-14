#include <R3D/Core/ThreadPool.h>

namespace r3d
{
    namespace core
    {
        // the constructor just launches some amount of workers
        ThreadPool::ThreadPool(size_t threads)
            :   stop(false)
        {
            for(size_t i = 0;i<threads;++i)
                m_Workers.emplace_back(
                    [this]
                    {
                        for(;;)
                        {
                            std::function<void()> task;

                            {
                                std::unique_lock<std::mutex> lock(this->m_QueueMutex);
                                this->m_Condition.wait(lock,
                                    [this]{ return this->stop || !this->m_Tasks.empty(); });
                                if(this->stop && this->m_Tasks.empty())
                                    return;
                                task = std::move(this->m_Tasks.front());
                                this->m_Tasks.pop();
                            }

                            task();
                        }
                    }
                );
        }

        // the destructor joins all threads
        ThreadPool::~ThreadPool()
        {
            {
                std::unique_lock<std::mutex> lock(m_QueueMutex);
                stop = true;
            }
            m_Condition.notify_all();
            for(std::thread &worker: m_Workers)
                worker.join();
        }
    }
}