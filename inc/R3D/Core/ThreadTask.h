#ifndef _R3D_CORE_THREADTASK_H_
#define _R3D_CORE_THREADTASK_H_

#include <functional>
#include <R3D/Core/TaskScheduler.h>
#include <R3D/Core/Task.h>
#include <R3D/Config.h>

namespace r3d
{
    namespace core
    {
        class ThreadTask: public Task
        {
        public:
            ThreadTask(TaskScheduler *ts, std::function<void()> work, Task *msg)
                : Task(), m_TaskScheduler(ts), m_Work(work), m_MessageTask(msg)
            {
                
            }
            virtual void execute()
            {
                ThreadPool &pool = m_TaskScheduler->getThreadPool();
                pool.enqueue([=](){
                    m_Work();
                    m_TaskScheduler->scheduleTask(NORMAL_PRIORITY, m_MessageTask);
                });
            }
        private:
            TaskScheduler *m_TaskScheduler;
            std::function<void()> m_Work;
            Task *m_MessageTask;
        };
    }
}

#endif