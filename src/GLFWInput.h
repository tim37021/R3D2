#ifndef _R3D_CORE_GLFWINPUT_H_
#define _R3D_CORE_GLFWINPUT_H_

#include <R3D/Core/Input.h>
#include <vector>

struct GLFWwindow;

namespace r3d
{
    namespace core
    {
        class GLFWInput: public Input
        {
        public:
            GLFWInput();
            GLFWInput(GLFWwindow *window);
            virtual ~GLFWInput()=default;

            virtual void update() override final;
            virtual bool isKeyDown(KeyCode) override final;
            virtual bool isKeyUp(KeyCode) override final;
            virtual bool isKeyHold(KeyCode) override final;

            virtual bool isMouseButtonDown(MouseButton) override final;
            virtual bool isMouseButtonUp(MouseButton) override final;
            virtual bool isMouseButtonHold(MouseButton) override final;
            virtual void getMousePosition(double *x, double *y) override final;
            virtual void setMousePosition(double x, double y) override final;

            void init();
            void setWindow(GLFWwindow *window);
        private:
            GLFWwindow *m_Window;
            std::vector<KeyCode> m_KeyUp, m_KeyDown;
            std::vector<MouseButton> m_MouseBtnUp, m_MouseBtnDown; 
            std::vector<bool> m_LastKeyState, m_LastMouseBtnState;

        };
    }
}

#endif