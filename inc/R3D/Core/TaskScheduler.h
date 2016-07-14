#ifndef _R3D_CORE_TASKSCHEDULER_H_
#define _R3D_CORE_TASKSCHEDULER_H_

#include <queue>
#include <mutex>
#include <utility>
#include <vector>
#include <R3D/Core/Task.h>
#include <R3D/Core/ThreadPool.h>
#include <R3D/Config.h>

namespace r3d
{
    namespace core
    {
        typedef std::pair<uint32_t, Task *> QueueNode;

        struct TaskOrder
        {
            bool operator()(const QueueNode &a, const QueueNode &b) const
            {
                return a.first>b.first;
            }
        };

        class TaskScheduler
        {
        public:
            TaskScheduler(): m_ThreadPool(THREADPOOL_COUNT)
            {

            }
            void scheduleTask(uint32_t priority, Task *);
            void step();

            ThreadPool &getThreadPool()
            { return m_ThreadPool; }
        private:
            std::priority_queue<QueueNode, std::vector<QueueNode>, 
                TaskOrder> m_Queue;
            std::mutex m_Mutex;

            ThreadPool m_ThreadPool;
        };
    }
}

#endif