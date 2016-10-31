#include <R3D/Rendering/TextureManager.h>
#include <R3D/Core/Device.h>
#include <R3D/Core/TaskScheduler.h>
#include "OpenGLTexture.h"

namespace r3d
{
    namespace rendering
    {
        TextureManager::TextureManager(core::Device *device)
            : m_Device(device)
        {
        }

        TextureManager::~TextureManager()
        {
            dispose();
        }

        void TextureManager::init()
        {
            m_DefaultTexture = registerTexture("DEFAULT_TEXTURE");
            rendering::Image img;
            img.loadFromFile("default.png");
            m_DefaultTexture->load(img);
        }

        void TextureManager::dispose()
        {
            for(auto &pair: m_TextureMap) {
                delete pair.second;
            }

            m_TextureMap.clear();
        }

        Texture *TextureManager::registerTexture(const std::string &name)
        {
            auto it = m_TextureMap.find(name);
            if(it == m_TextureMap.cend()) {
                return (m_TextureMap[name] = new OpenGLTexture());
            }else
                return it->second;
        }

        Texture *TextureManager::fetchTexture(const std::string &name) const
        {
            auto it = m_TextureMap.find(name);
            return (it == m_TextureMap.cend()? m_DefaultTexture: it->second);
        }

        void TextureManager::loadTextureFromFileAsync(const std::string &name, const std::string &filename, core::TaskStatus *status)
        {
            m_Device->getTaskScheduler()->getThreadPool().enqueue([=](){
                // In thread
                Image *image = new Image();
                image->loadFromFile(filename);
                if(image->isValid()) {
                    m_Device->getTaskScheduler()->scheduleTask(NORMAL_PRIORITY, [=](){
                        // In main thread
                        Texture *texture = registerTexture(name);
                        texture->load(*image);
                        delete image;
                    }, status);
                } else
                    *status = core::TaskStatus::TASK_READY;
            });
        }
    }
}