#ifndef _R3D_OPENGLRENDERTARGET_H_
#define _R3D_OPENGLRENDERTARGET_H_
#include <R3D/Rendering/RenderTarget.h>
#include <GL/glew.h>

namespace r3d
{
	namespace rendering
	{
		class OpenGLRenderTarget: public RenderTarget
		{
			friend OpenGLRenderTarget *GetDefaultOpenGLRenderTarget();
		public:
			OpenGLRenderTarget();
			virtual ~OpenGLRenderTarget();
			virtual void attachTextures(const std::vector<Texture *> &textures) override;
			virtual void attachDepthTexture(Texture *texture) override;
			virtual void bind() override;

			GLuint getID() const
			{ return m_Id; }
		private:
			OpenGLRenderTarget(GLuint id);
			GLuint m_Id;
		};

		OpenGLRenderTarget *GetDefaultOpenGLRenderTarget();
	}
}

#endif