#include <R3D/Rendering/ShaderProgram.h>
#include <cstdio>

namespace r3d
{
	namespace rendering
	{
		ShaderProgram::ShaderProgram()
		{
			m_Id = glCreateProgram();
		}

		ShaderProgram::~ShaderProgram()
		{
			glDeleteProgram(m_Id);
		}

		void ShaderProgram::use()
		{
			glUseProgram(m_Id);
		}

		void ShaderProgram::create(const char *vs, const char *fs)
		{
			glAttachShader(m_Id, createShader(GL_VERTEX_SHADER, vs));
			glAttachShader(m_Id, createShader(GL_FRAGMENT_SHADER, fs));
			glLinkProgram(m_Id);

			int32_t status, max_length;
			glGetProgramiv(m_Id, GL_LINK_STATUS, &status);
			if(!status) {
				glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &max_length);
				char *info_log = new char[max_length];
				glGetProgramInfoLog(m_Id, max_length, &max_length, info_log);

				fprintf(stderr, "Link Error: %s\n", info_log);
				delete [] info_log;
			}
		}

		GLuint ShaderProgram::createShader(GLuint type, const char *source)
		{
		    GLuint shader = glCreateShader(type);
		    glShaderSource(shader, 1, (const GLchar **) &source, nullptr);

		    glCompileShader(shader);

		    int status, max_length;
		    char *infoLog = nullptr;
		    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		    if (!status) {
		        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

		        /* The maxLength includes the NULL character */
		        infoLog = new char[max_length];

		        glGetShaderInfoLog(shader, max_length, &max_length, infoLog);

		        fprintf(stderr, "Shader Error: %s\n", infoLog);

		        /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
		        /* In this simple program, we'll just leave */
		        delete[] infoLog;
		        return 0;
		    }

		    return shader;
		}

		void ShaderProgram::setUniform(const std::string &name, int32_t value) 
		{
			GLint id = glGetUniformLocation(m_Id, name.c_str());
			if(id != -1) {
				glUseProgram(m_Id);
				glUniform1i(id, value);
			}
		}
	}
}