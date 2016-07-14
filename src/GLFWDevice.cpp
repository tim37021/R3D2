#include "GLFWDevice.h"
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
            m_Input.init();
        }

        GLFWDevice::~GLFWDevice() 
        {
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

        void GLFWDevice::update()
        {
            m_TaskScheduler.step();
            glfwMakeContextCurrent(m_Window);
            glfwPollEvents();
        }

        void GLFWDevice::swapBuffers()
        {
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