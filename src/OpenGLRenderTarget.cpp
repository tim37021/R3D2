#include "OpenGLRenderTarget.h"
#include "OpenGLTexture.h"

namespace r3d
{
	namespace rendering
	{
		OpenGLRenderTarget::OpenGLRenderTarget()
			: RenderTarget()
		{
			glGenFramebuffers(1, &m_Id);
		}

		OpenGLRenderTarget::OpenGLRenderTarget(GLuint id)
			: RenderTarget(), m_Id(id)
		{
			
		}

		OpenGLRenderTarget::~OpenGLRenderTarget()
		{
			if(m_Id!=0)
				glDeleteFramebuffers(1, &m_Id);
		}

		void OpenGLRenderTarget::attachTextures(const std::vector<Texture *> &textures) 
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Id);
			std::vector<GLenum> draw_buffers(textures.size());
			for(uint32_t i=0; i<textures.size(); i++) {
				draw_buffers[i] = GL_COLOR_ATTACHMENT0+i;
				OpenGLTexture *ogl_texture = reinterpret_cast<OpenGLTexture *>(textures[i]);
				glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, 
					ogl_texture->getID(), 0);
			}
			glDrawBuffers(draw_buffers.size(), draw_buffers.data());
		}

		void OpenGLRenderTarget::attachDepthTexture(Texture *texture) 
		{
			OpenGLTexture *ogl_texture = reinterpret_cast<OpenGLTexture *>(texture);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Id);
			glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 
				ogl_texture->getID(), 0);
		}

		void OpenGLRenderTarget::bind()
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Id);
		}

		OpenGLRenderTarget *GetDefaultOpenGLRenderTarget()
		{
			static OpenGLRenderTarget default_rt(0);
			return &default_rt;
		}
	}
}