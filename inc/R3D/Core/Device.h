#ifndef _R3D_CORE_DEVICE_H_
#define _R3D_CORE_DEVICE_H_

#include <cstdint>
#include <string>
#include <R3D/Core/Math.h>
#include <R3D/Core/TaskScheduler.h>
#include <R3D/Core/Input.h>

namespace r3d
{
    namespace core
    {
        class TaskScheduler;
        class Device
        {
        public:
            virtual ~Device()=default;
            TaskScheduler *getTaskScheduler()
            { return &m_TaskScheduler; }
            virtual Input *getInput()=0;
            virtual void setWindowCaption(const std::string &caption)=0;
            virtual bool isRunning() const =0;
            virtual void stop() =0;
            virtual void update()=0;
            virtual void swapBuffers()=0;
            virtual void setSwapInterval(uint32_t)=0;
            virtual double getTime() const =0;
        protected:
            TaskScheduler m_TaskScheduler;
        };

        Device *CreateDevice(Vector2i size, const std::string &caption);
        void DestroyDevice(Device *);
    }
}

#endif