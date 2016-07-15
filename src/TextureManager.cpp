#include <R3D/Rendering/TextureManager.h>
#include "OpenGLTexture.h"

namespace r3d
{
    namespace rendering
    {
        TextureManager::~TextureManager()
        {
            dispose();
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
    }
}