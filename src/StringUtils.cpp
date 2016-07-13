#include <R3D/Utils/StringUtils.h>
#include <cctype>

namespace r3d
{
    namespace utils
    {
        std::string ToUppercase(const std::string &str)
        {
            std::string result;
            for(auto &c: str)
                result+=toupper(c);
            return result;
        }
    }
}