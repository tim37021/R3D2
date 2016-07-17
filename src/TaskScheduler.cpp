#include <R3D/Core/TaskScheduler.h>

namespace r3d
{
    namespace core
    {
        TaskScheduler::TaskScheduler()
            : m_ThreadPool(THREADPOOL_COUNT), m_Counter(0)
        {

        }

        void TaskScheduler::scheduleTask(uint32_t priority, std::function<void ()> task, TaskStatus *status)
        {
            m_Mutex.lock();
            if(status)
                *status = TaskStatus::TASK_QUEUING;
            m_Queue.push({{priority, m_Counter++}, task, status});
            m_Mutex.unlock();
        }

        void TaskScheduler::step()
        {
            m_Mutex.lock();
            if(!m_Queue.empty()) {
                std::function<void ()> top_task = m_Queue.top().m_Task;
                TaskStatus *status = m_Queue.top().m_Status;
                m_Queue.pop();
                m_Mutex.unlock();

                top_task();
                if(status)
                    *status = TaskStatus::TASK_READY;
            }else
                m_Mutex.unlock();
        }
    }
}