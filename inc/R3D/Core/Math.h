#ifndef _R3D_CORE_MATH_H_
#define _R3D_CORE_MATH_H_

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace r3d
{
    namespace core
    {
        typedef glm::ivec2 Vector2i;
        typedef glm::vec2 Vector2f;
        typedef glm::ivec3 Vector3i;
        typedef glm::ivec4 Vector4i;
        typedef glm::vec3 Vector3f;
        typedef glm::vec4 Vector4f;

        typedef glm::vec4 Color;

        typedef glm::mat3 Matrix3;
        typedef glm::mat4 Matrix4;

        struct Vertex {
            Vector3f m_Pos;
            Vector2f m_TexCoord;
            Vector3f m_Normal;
        };

        static inline Matrix4 Perspective(float fovy, float aspect, float near, float far)
        { return glm::perspective(fovy, aspect, near, far); }

        static inline Matrix4 LookAt(const Vector3f &center, const Vector3f &target, const Vector3f &up)
        { return glm::lookAt(center, target, up); }

        template<typename genType >
        static inline auto Cross(genType const &vec1, genType const &vec2) -> decltype(glm::cross(vec1, vec2))
        { return glm::cross(vec1, vec2); }

        template<typename genType >
        static inline auto ValuePointer(genType const &vec) -> decltype(glm::value_ptr(vec))
        { return glm::value_ptr(vec); }
    }
}

#endif