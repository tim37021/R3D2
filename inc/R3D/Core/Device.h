#ifndef _R3D_CORE_DEVICE_H_
#define _R3D_CORE_DEVICE_H_

#include <R3D/Core/Math.h>
#include <R3D/Core/TaskScheduler.h>
#include <string>

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
            { return m_TaskScheduler; }
            virtual void setWindowCaption(const std::string &caption)=0;
            virtual bool isRunning()=0;
            virtual void pollEvents()=0;
            virtual void swapBuffers()=0;
            virtual double getTime()=0;
        private:
            TaskScheduler *m_TaskScheduler;
        };

        Device *CreateDevice(Vector2i size, const std::string &caption);
        void DestroyDevice(Device *);
    }
}

#endif