#ifndef _R3D_CORE_EXCEPTION_H_
#define _R3D_CORE_EXCEPTION_H_

#include <stdexcept>
#include <string>

namespace r3d
{
    namespace core
    {
        class InvalidOperation: public std::runtime_error
        {
        public:
            InvalidOperation(const std::string &msg): std::runtime_error(msg)
            {

            }
        };

        class DeviceCreationError: public std::runtime_error
        {
        public:
            DeviceCreationError(const std::string &msg): std::runtime_error(msg)
            {
                
            }
        };
    }
}

#endif