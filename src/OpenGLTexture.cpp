#include "OpenGLTexture.h"

namespace r3d
{
    namespace rendering
    {
        OpenGLTexture::OpenGLTexture()
        {
            glGenTextures(1, &m_Id);
        }

        OpenGLTexture::~OpenGLTexture()
        {
            glDeleteTextures(1, &m_Id);
        }

        bool OpenGLTexture::create(core::Vector2i size, PixelFormat pf)
        {
            return false;
        }

        bool OpenGLTexture::load(Image &img)
        {
            glBindTexture(GL_TEXTURE_2D, m_Id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
            return true;
        }

        void OpenGLTexture::bind(uint32_t channel)
        {
            glActiveTexture(GL_TEXTURE0+channel);
            glBindTexture(GL_TEXTURE_2D, m_Id);
        }
    }
}