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
        struct Priority{
            uint32_t m_Priority;
            uint64_t m_TimeStamp;
            Priority(uint32_t priority, uint64_t timestamp): m_Priority(priority), m_TimeStamp(timestamp)
            {

            }

            bool operator<(const Priority &rhs) const {
                if(m_Priority == rhs.m_Priority)
                    return m_TimeStamp < rhs.m_TimeStamp;
                else
                    return m_Priority > rhs.m_Priority;
            }
        };
        typedef std::pair<Priority, Task *> QueueNode;

        class TaskScheduler
        {
        public:
            TaskScheduler();
            void scheduleTask(uint32_t priority, Task *);
            void step();

            ThreadPool &getThreadPool()
            { return m_ThreadPool; }
        private:
            std::priority_queue<QueueNode, std::vector<QueueNode>> m_Queue;
            std::mutex m_Mutex;

            ThreadPool m_ThreadPool;
            uint64_t m_Counter;
        };
    }
}

#endif