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
            Task(uint32_t priority): m_Priority(priority)
            {
                
            }
            ~Task()=default;
            virtual void execute()=0;
            // methods belows are only meaningful in async task
            virtual bool isRunning() const
            {
                return false;
            }

            virtual float getProgress() const
            {
                return 1.0f;
            }
            
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