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
            ~TextureManager();

            void dispose();
            Texture *registerTexture(const std::string &name);
        private:
            std::map<std::string, Texture *> m_TextureMap;
        };
    }
}

#endif