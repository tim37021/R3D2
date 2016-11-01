#ifndef _GLFWDEVICE_H_
#define _GLFWDEVICE_H_

#include <cstdint>
#include <R3D/Core/Device.h>
#include <R3D/Core/TaskScheduler.h>
#include <R3D/Rendering/TextureManager.h>
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
            virtual TaskScheduler *getTaskScheduler() override final
            { return &m_TaskScheduler;  }
            virtual Input *getInput() override final;
            virtual rendering::TextureManager *getTextureManager() override final
            { return &m_TextureManager; }
            virtual void setWindowCaption(const std::string &caption) override final;
            virtual bool isRunning() const override final;
            virtual void stop() override final;
            virtual void update() override final;
            virtual void setSwapInterval(uint32_t interval) override final;
            virtual void swapBuffers() override final;
            virtual double getTime() const override final;
            virtual rendering::RenderTarget *addRenderTarget() override final;
            virtual rendering::RenderTarget *getDefaultRenderTarget() override final;
        private:
            GLFWwindow *m_Window;
            GLFWInput m_Input;
            TaskScheduler m_TaskScheduler;
            rendering::TextureManager m_TextureManager;
        };
    }
}

#endif