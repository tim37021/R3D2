#ifndef _R3D_RENDERING_TEXTUREMANAGER_H_
#define _R3D_RENDERING_TEXTUREMANAGER_H_

#include <map>
#include <future>
#include <R3D/Rendering/Texture.h>

namespace r3d
{
    namespace core
    {
        class Device;
        enum class TaskStatus;
    }

    namespace rendering
    {
        class TextureManager
        {
        public:
            TextureManager(core::Device *device);
            ~TextureManager();

            void init();
            void dispose();
            Texture *registerTexture(const std::string &name);
            Texture *fetchTexture(const std::string &name) const;

            void loadTextureFromFileAsync(const std::string &name, const std::string &filename, core::TaskStatus *status=nullptr);
        private:
            core::Device *m_Device;
            std::map<std::string, Texture *> m_TextureMap;
            Texture *m_DefaultTexture;
        };
    }
}

#endif