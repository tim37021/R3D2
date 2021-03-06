#ifndef _R3D_RENDERING_IMAGE_H_
#define _R3D_RENDERING_IMAGE_H_

#include <string>
#include <cstdint>
#include <vector>
#include <R3D/Core/Math.h>

namespace r3d
{
    namespace rendering
    {
        class Image
        {
        public:
            Image();
            Image(const std::string &filename);

            void dispose();
            void loadFromFile(const std::string &filename);

            bool isValid() const
            { return m_Size.x*m_Size.y!=0; }

            core::Vector2i getSize() const
            { return m_Size; }

            const uint8_t *getData() const
            { return m_Data.data(); }
        private:
            std::vector<uint8_t> m_Data;
            core::Vector2i m_Size;
        };
    }
}

#endif