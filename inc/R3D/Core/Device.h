#ifndef _R3D_CORE_DEVICE_H_
#define _R3D_CORE_DEVICE_H_

#include <cstdint>
#include <string>
#include <R3D/Core/Math.h>
#include <R3D/Core/TaskScheduler.h>
#include <R3D/Rendering/TextureManager.h>
#include <R3D/Scene/SceneManager.h>
#include <R3D/Core/Input.h>
#include <R3D/Rendering/RenderTarget.h>
#include <R3D/Rendering/ShaderProgram.h>

namespace r3d
{
    namespace core
    {
        class TaskScheduler;
        class Device
        {
        public:
            virtual ~Device()
            {
                for(auto target: m_RenderTargets)
                    delete target;
                for(auto program: m_ShaderPrograms)
                    delete program;
            }
            virtual TaskScheduler *getTaskScheduler()=0;
            virtual Input *getInput()=0;
            virtual rendering::TextureManager *getTextureManager()=0;
            virtual scene::SceneManager *getSceneManager()=0;
            virtual void setWindowCaption(const std::string &caption)=0;
            virtual bool isRunning() const =0;
            virtual void stop()=0;
            virtual void update()=0;
            virtual void swapBuffers()
            {
                m_FrameRate = 1.0/(getTime() - m_LastUpdateTime);
                m_LastUpdateTime = getTime();
            }

            virtual void setSwapInterval(uint32_t)=0;
            virtual double getTime() const =0;

            virtual rendering::RenderTarget *addRenderTarget()=0;
            virtual rendering::RenderTarget *getDefaultRenderTarget()=0;
            rendering::ShaderProgram *addShaderProgram()
            { return new rendering::ShaderProgram(); }

            float getFrameRate() const
            {
                return m_FrameRate;
            }
        protected:
            std::vector<rendering::RenderTarget *> m_RenderTargets;
            std::vector<rendering::ShaderProgram *> m_ShaderPrograms;
        private:
            float m_LastUpdateTime;
            float m_FrameRate;
        };

        Device *CreateDevice(Vector2i size, const std::string &caption);
        void DestroyDevice(Device *);
    }
}

#endif