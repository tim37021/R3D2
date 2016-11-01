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
            glBindTexture(GL_TEXTURE_2D, m_Id);
            GLenum internal, dataformat, datatype;
            switch(pf) {
                case PixelFormat::PF_D24:
                    internal = GL_DEPTH_COMPONENT24; dataformat = GL_DEPTH_COMPONENT; datatype = GL_FLOAT; break;
                case PixelFormat::PF_D32:
                    internal = GL_DEPTH_COMPONENT32; dataformat = GL_DEPTH_COMPONENT; datatype = GL_FLOAT; break;
                case PixelFormat::PF_R8G8B8:
                    internal = GL_RGB; dataformat = GL_RGB; datatype = GL_UNSIGNED_BYTE; break;
                case PixelFormat::PF_R8G8B8A8:
                    internal = GL_RGBA; dataformat = GL_RGBA; datatype = GL_UNSIGNED_BYTE; break;
            }
            glTexImage2D(GL_TEXTURE_2D, 0, internal, size.x, size.y, 0, 
                dataformat, datatype, nullptr);
            m_Size = size;

            return true;
        }

        bool OpenGLTexture::load(Image &img)
        {
            glBindTexture(GL_TEXTURE_2D, m_Id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            m_Size = img.getSize();
            return true;
        }

        void OpenGLTexture::bind(uint32_t channel)
        {
            glActiveTexture(GL_TEXTURE0+channel);
            glBindTexture(GL_TEXTURE_2D, m_Id);
        }
    }
}