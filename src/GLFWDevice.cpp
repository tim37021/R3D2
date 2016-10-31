#include "GLFWDevice.h"
#include "OpenGLRenderTarget.h"
#include <R3D/Core/Exception.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

static uint32_t TotalWindowCount;

namespace r3d
{
    namespace core
    {
        GLFWDevice::GLFWDevice(Vector2i size, const std::string &caption)
            : m_TextureManager(this)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            m_Window = glfwCreateWindow(size.x, size.y, caption.c_str(), nullptr, nullptr);
            if(!m_Window)
                throw DeviceCreationError("Cannot create window with GLFW3");

            glfwMakeContextCurrent(m_Window);

            glewExperimental = GL_TRUE;
            glewInit();

            glfwSwapInterval(0);

            m_Input.setWindow(m_Window);

            // Init must be called after context is made current
            m_Input.init();
            m_TextureManager.init();
        }

        GLFWDevice::~GLFWDevice() 
        {
            glfwMakeContextCurrent(m_Window);
            m_TextureManager.dispose();
            glfwDestroyWindow(m_Window);
        }

        Input *GLFWDevice::getInput()
        {
            return &m_Input;
        }

        void GLFWDevice::setWindowCaption(const std::string &caption)
        {
            glfwSetWindowTitle(m_Window, caption.c_str());
        }

        bool GLFWDevice::isRunning() const
        {
            return !glfwWindowShouldClose(m_Window);
        }

        void GLFWDevice::stop() 
        {
            glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
        }

        void GLFWDevice::update()
        {
            if(glfwGetCurrentContext()!=m_Window)
                glfwMakeContextCurrent(m_Window);
            glfwPollEvents();
            m_Input.update();
            m_TaskScheduler.step();
        }

        void GLFWDevice::swapBuffers()
        {
            Device::swapBuffers();
            glfwSwapBuffers(m_Window);
        }

        void GLFWDevice::setSwapInterval(uint32_t interval)
        {
            glfwMakeContextCurrent(m_Window);
            glfwSwapInterval(interval);
        }

        double GLFWDevice::getTime() const
        {
            return glfwGetTime();
        }

        rendering::RenderTarget *GLFWDevice::addRenderTarget() 
        {
            rendering::RenderTarget *result = new rendering::OpenGLRenderTarget();
            m_RenderTargets.push_back(result);
            return result;
        }

        Device *CreateDevice(Vector2i size, const std::string &caption)
        {
            if(!TotalWindowCount)
                glfwInit();
            TotalWindowCount++;

            return new GLFWDevice(size, caption);
        }
        
        void DestroyDevice(Device *device)
        {
            TotalWindowCount--;
            delete device;

            if(!TotalWindowCount)
                glfwTerminate();
        }
    }
}