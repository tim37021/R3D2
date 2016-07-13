#ifndef _R3D_CORE_TASK_H_
#define _R3D_CORE_TASK_H_

#include <cstdint>

namespace r3d
{
    namespace core
    {
        class Task
        {
        public:
            Task(uint32_t priority);
            ~Task()=default;
            virtual void execute()=0;
            virtual bool isRunning() const =0;
            // This method is only meaningful in async task
            virtual float getProgress() const =0;
            
            bool operator<(const Task &rhs) const
            {
                return m_Priority>rhs.m_Priority;
            }
        private:
            uint32_t m_Priority;
        };
    }
}

#endif