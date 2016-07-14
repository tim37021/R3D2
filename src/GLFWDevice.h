#ifndef _GLFWDEVICE_H_
#define _GLFWDEVICE_H_

#include <cstdint>
#include <R3D/Core/Device.h>
#include "GLFWInput.h"

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
            virtual Input *getInput() override final;
            virtual void setWindowCaption(const std::string &caption) override final;
            virtual bool isRunning() const override final;
            virtual void stop() override final;
            virtual void update() override final;
            virtual void setSwapInterval(uint32_t interval) override final;
            virtual void swapBuffers() override final;
            virtual double getTime() const override final;
        private:
            GLFWwindow *m_Window;
            GLFWInput m_Input;
        };
    }
}

#endif