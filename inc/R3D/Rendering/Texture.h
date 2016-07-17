#ifndef _R3D_RENDERING_TEXTURE_H_
#define _R3D_RENDERING_TEXTURE_H_

#include <R3D/Core/Math.h>
#include <R3D/Rendering/Image.h>

namespace r3d
{
    namespace rendering
    {
        enum class PixelFormat{
            PF_RGB24,
            PF_RGBA32
        };

        class TextureManager;

        class Texture
        {
            friend class TextureManager;
        public:
            virtual ~Texture()=default;

            virtual bool create(core::Vector2i size, PixelFormat pf)=0;

            /*
            Load image data to video card 
            img: Image object
            return value: nothing
            */
            virtual bool load(Image &img)=0;
            virtual void bind(uint32_t channel)=0;
            core::Vector2i getSize() const
            { return m_Size; }
        protected:
            Texture()=default;
            core::Vector2i m_Size;
        private:
            Texture &operator=(const Texture &);
        };
    }
}

#endif