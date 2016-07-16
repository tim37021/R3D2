#include <R3D/Core/TaskScheduler.h>

namespace r3d
{
    namespace core
    {
        TaskScheduler::TaskScheduler()
            : m_ThreadPool(THREADPOOL_COUNT), m_Counter(0)
        {

        }

        void TaskScheduler::scheduleTask(uint32_t priority, Task *task)
        {
            m_Mutex.lock();
            m_Queue.push({{priority, m_Counter++}, task});
            m_Mutex.unlock();
        }

        void TaskScheduler::step()
        {
            m_Mutex.lock();
            if(!m_Queue.empty()) {
                Task *top_task = m_Queue.top().second;
                m_Queue.pop();
                m_Mutex.unlock();

                top_task->execute();
            }else
                m_Mutex.unlock();
        }
    }
}