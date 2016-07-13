#ifndef _GLFWDEVICE_H_
#define _GLFWDEVICE_H_

#include <cstdint>
#include <R3D/Core/Device.h>

struct GLFWwindow;

namespace r3d
{
    namespace core
    {
        class GLFWDevice: public Device
        {
        public:
            GLFWDevice(Vector2i size, const std::string &caption);
            ~GLFWDevice();
            virtual void setWindowCaption(const std::string &caption);
            virtual bool isRunning();
            virtual void update();
            virtual void setSwapInterval(uint32_t interval);
            virtual void swapBuffers();
            virtual double getTime();
        private:
            GLFWwindow *m_Window;
        };
    }
}

#endif