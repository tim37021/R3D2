#include <R3D/Core/TaskScheduler.h>

namespace r3d
{
    namespace core
    {
        void TaskScheduler::scheduleTask(Task *task)
        {
            m_Mutex.lock();
            m_Queue.push(task);
            m_Mutex.unlock();
        }

        void TaskScheduler::step()
        {
            m_Mutex.lock();
            if(!m_Queue.empty()) {
                Task *top_task = m_Queue.top();
                m_Queue.pop();
                m_Mutex.unlock();

                top_task->execute();
            }else
                m_Mutex.unlock();
        }
    }
}