#ifndef _R3D_CORE_TASKSCHEDULER_H_
#define _R3D_CORE_TASKSCHEDULER_H_

#include <queue>
#include <R3D/Core/Task.h>
#include <mutex>

namespace r3d
{
    namespace core
    {
        class TaskScheduler
        {
        public:
            void scheduleTask(Task *);
            void step();
        private:
            std::priority_queue<Task *> m_Queue;
            std::mutex m_Mutex;
        };
    }
}

#endif