#ifndef _R3D_RENDERING_SHADERPROGRAM_H_
#define _R3D_RENDERING_SHADERPROGRAM_H_

#include <string>
#include <cstdint>
#include <R3D/Core/Math.h>
#include <GL/glew.h>

namespace r3d
{
	namespace rendering
	{
		class ShaderProgram
		{
		public:
			ShaderProgram();
			~ShaderProgram();
			void use();
			void create(const char *vs, const char *fs);
			void setUniform(const std::string &name, int32_t value);
			void setUniform(const std::string &name, core::Vector2i value);
			void setUniform(const std::string &name, float value);
			void setUniform(const std::string &name, core::Vector2f value);
			void setUniform(const std::string &name, core::Vector3f value);
			void setUniform(const std::string &name, core::Vector4f value);
			void setUniform(const std::string &name, const core::Matrix4 &value);
		private:
			GLuint m_Id;
			GLuint createShader(GLenum type, const char *source);
		};
	}
}

#endif