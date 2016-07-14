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
            Task()=default;
            ~Task()=default;
            virtual void execute()=0;
        };
    }
}

#endif