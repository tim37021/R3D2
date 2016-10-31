#ifndef _R3D_RENDERING_OPENGLTEXTURE_H_
#define _R3D_RENDERING_OPENGLTEXTURE_H_

#include <GL/glew.h>
#include <R3D/Rendering/Texture.h>

namespace r3d
{
    namespace rendering
    {
        class OpenGLTexture: public Texture
        {
        public:
            OpenGLTexture();
            virtual ~OpenGLTexture();
            virtual bool create(core::Vector2i size, PixelFormat pf) override;
            virtual bool load(Image &img) override;
            virtual void bind(uint32_t channel) override;

            GLuint getID() const
            { return m_Id; }
        private:
            GLuint m_Id;
        };
    }
}

#endif