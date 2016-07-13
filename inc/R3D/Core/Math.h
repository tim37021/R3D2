#ifndef _R3D_CORE_MATH_H_
#define _R3D_CORE_MATH_H_

#include <cstdint>
#include <atomic>

namespace r3d
{
    namespace core
    {
        template <class T>
        struct Vector2
        {
            T x, y;
            Vector2(T x_, T y_)
                : x(x_), y(y_) 
            {
            }

            const Vector2 operator+(const Vector2 &rhs) const
            {
                return Vector2(x+rhs.x, y+rhs.y);
            }

            const Vector2 operator-(const Vector2 &rhs) const
            {
                return Vector2(x-rhs.x, y-rhs.y);
            }
        };

        template <class T>
        struct Vector3
        {
            T x, y, z;
            Vector3(T x_, T y_, T z_)
                : x(x_), y(y_), z(z_)
            {
            }

            const Vector3 operator+(const Vector3 &rhs) const
            {
                return Vector3(x+rhs.x, y+rhs.y, z+rhs.z);
            }

            const Vector3 operator-(const Vector3 &rhs) const
            {
                return Vector3(x-rhs.x, y-rhs.y, z-rhs.z);
            }

            const Vector3 operator*(const Vector3 &rhs) const
            {
                return Vector3(x*rhs.x, y*rhs.y, z*rhs.z);
            }

            const Vector3 operator*(T scalar) const
            {
                return Vector3(x*scalar, y*scalar, z*scalar);
            }
        };

        template <class T>
        struct Vector4
        {
            T x, y, z, w;
            Vector4(T x_, T y_, T z_, T w_)
                : x(x_), y(y_), z(z_), w(w_)
            {
            }

            const Vector4 operator+(const Vector4 &rhs) const
            {
                return Vector4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
            }

            const Vector4 operator-(const Vector4 &rhs) const
            {
                return Vector4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
            }

            const Vector4 operator*(const Vector4 &rhs) const
            {
                return Vector4(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w);
            }

            const Vector4 operator*(T scalar) const
            {
                return Vector4(x*scalar, y*scalar, z*scalar, w*scalar);
            }
        };

        typedef Vector2<uint32_t> Vector2i;
        typedef Vector2<float> Vector2f;
        typedef Vector3<uint32_t> Vector3i;
        typedef Vector3<float> Vector3f;
        typedef Vector4<float> Vector4f;

        typedef Vector4f Color;
    }
}

#endif