#include <R3D/Rendering/Image.h>
#include <R3D/Utils/StringUtils.h>

#include <lodepng.h>

namespace r3d
{
    namespace rendering
    {
        Image::Image()
        {

        }

        Image::Image(const std::string &filename)
        {
            loadFromFile(filename);
        }

        void Image::dispose()
        {
            std::vector<uint8_t> t;
            m_Data.swap(t);
        }

        void Image::loadFromFile(const std::string &filename)
        {
            std::vector<uint8_t> file_contents;
            if(utils::ToUppercase(filename.substr(filename.length()-4))==".PNG") {
                lodepng::load_file(file_contents, filename.c_str());
                uint32_t width, height;
                lodepng::decode(m_Data, width, height, file_contents);
                m_Size = {width, height};
            }
        }
    }
}