#ifndef _R3D_CORE_TASK_H_
#define _R3D_CORE_TASK_H_

#include <cstdint>
#include <functional>

namespace r3d
{
    namespace core
    {
        class Task
        {
        public:
            Task()=default;
            virtual ~Task()=default;
            virtual void execute()=0;
        };

        class QuickTask: public Task
        {
        public:
            QuickTask(std::function<void()> work)
                : m_Work(work)
            {

            }
            virtual ~QuickTask()=default;
            virtual void execute()
            {
                m_Work();
            }
        private:
            std::function<void()> m_Work;
        };
    }
}

#endif