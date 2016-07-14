#ifndef _R3D_CORE_THREADPOOL_H_
#define _R3D_CORE_THREADPOOL_H_

// Source: https://github.com/progschj/ThreadPool/blob/master/ThreadPool.h

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <R3D/Core/Exception.h>

namespace r3d
{
    namespace core
    {
        class ThreadPool
        {
        public:
            ThreadPool(size_t count);
            template<class F, class... Args>
            auto enqueue(F&& f, Args&&... args) 
                -> std::future<typename std::result_of<F(Args...)>::type>;
            ~ThreadPool();
        private:
            // Need to keep track of threads so we can join them
            std::vector<std::thread> m_Workers;
            // The task queue
            std::queue<std::function<void()>> m_Tasks;

            std::mutex m_QueueMutex;
            std::condition_variable m_Condition;
            bool stop;
        };

        // add new work item to the pool
        template<class F, class... Args>
        auto ThreadPool::enqueue(F&& f, Args&&... args) 
            -> std::future<typename std::result_of<F(Args...)>::type>
        {
            using return_type = typename std::result_of<F(Args...)>::type;

            auto task = std::make_shared< std::packaged_task<return_type()> >(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                );
                
            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(m_QueueMutex);

                // don't allow enqueueing after stopping the pool
                if(stop)
                    throw InvalidOperation("enqueue on stopped ThreadPool");

                m_Tasks.emplace([task](){ (*task)(); });
            }
            m_Condition.notify_one();
            return res;
        }
    }
}

#endif