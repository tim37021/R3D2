#include "GLFWInput.h"
#include <GLFW/glfw3.h>
#include <algorithm>

static int GLFWKeyMap[]={GLFW_KEY_UNKNOWN, GLFW_KEY_A, GLFW_KEY_B, GLFW_KEY_C, 
    GLFW_KEY_D, GLFW_KEY_E, GLFW_KEY_F, GLFW_KEY_G, GLFW_KEY_H, GLFW_KEY_I,
    GLFW_KEY_J, GLFW_KEY_K, GLFW_KEY_L, GLFW_KEY_M, GLFW_KEY_N, GLFW_KEY_O, 
    GLFW_KEY_P, GLFW_KEY_Q, GLFW_KEY_R, GLFW_KEY_S, GLFW_KEY_T, GLFW_KEY_U, 
    GLFW_KEY_V, GLFW_KEY_W, GLFW_KEY_X, GLFW_KEY_Y, GLFW_KEY_Z, GLFW_KEY_LEFT, 
    GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_ENTER, GLFW_KEY_ESCAPE};

namespace r3d
{
    namespace core
    {
        GLFWInput::GLFWInput()
        {
        }
        GLFWInput::GLFWInput(GLFWwindow *window)
            : m_Window(window)
        {
        }

        void GLFWInput::init()
        {
            m_LastKeyState.resize(static_cast<int>(KeyCode::KEY_LAST));

            for(int i=0; i<static_cast<int>(KeyCode::KEY_LAST); i++)
                m_LastKeyState[i] = (glfwGetKey(m_Window, GLFWKeyMap[static_cast<int>(i)])==GLFW_PRESS);
        }

        void GLFWInput::update()
        {
            m_KeyDown.clear();
            m_KeyUp.clear();
            for(int i=0; i<static_cast<int>(KeyCode::KEY_LAST); i++) {
                bool state = (glfwGetKey(m_Window, GLFWKeyMap[static_cast<int>(i)])==GLFW_PRESS);
                if(state!=m_LastKeyState[i]) {
                    if(state)
                        m_KeyDown.push_back(static_cast<KeyCode>(i));
                    else   
                        m_KeyUp.push_back(static_cast<KeyCode>(i));
                }
                m_LastKeyState[i] = state;
            }
        }

        bool GLFWInput::isKeyDown(KeyCode key)
        {
            auto it = std::lower_bound(m_KeyDown.cbegin(), m_KeyDown.cend(), key);
            return (it!=m_KeyDown.cend() && *it==key);
        }

        bool GLFWInput::isKeyUp(KeyCode key)
        {
            auto it = std::lower_bound(m_KeyUp.cbegin(), m_KeyUp.cend(), key);
            return (it!=m_KeyUp.cend() && *it == key);
        }

        bool GLFWInput::isKeyHold(KeyCode key)
        {
            return glfwGetKey(m_Window, GLFWKeyMap[static_cast<int>(key)])==GLFW_PRESS;
        }

        void GLFWInput::setWindow(GLFWwindow *window)
        {
            m_Window = window;
        }
    }
}