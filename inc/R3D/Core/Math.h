#ifndef _R3D_CORE_MATH_H_
#define _R3D_CORE_MATH_H_

#include <glm/glm.hpp>

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
    }
}

#endif