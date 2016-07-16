#ifndef _R3D_RENDERING_TEXTUREMANAGER_H_
#define _R3D_RENDERING_TEXTUREMANAGER_H_

#include <map>
#include <R3D/Rendering/Texture.h>

namespace r3d
{
    namespace rendering
    {
        class TextureManager
        {
        public:
            TextureManager();
            ~TextureManager();

            void init();
            void dispose();
            Texture *registerTexture(const std::string &name);
            Texture *fetchTexture(const std::string &name) const;
        private:
            std::map<std::string, Texture *> m_TextureMap;
            Texture *m_DefaultTexture;
        };
    }
}

#endif