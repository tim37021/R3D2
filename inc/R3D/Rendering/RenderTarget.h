#ifndef _R3D_RENDERING_RENDERTARGET_H_
#define _R3D_RENDERING_RENDERTARGET_H_
#include <vector>

namespace r3d
{
	namespace rendering
	{
		class Texture;
		class RenderTarget
		{
		public:
			virtual ~RenderTarget(){}
			virtual void attachTextures(const std::vector<Texture *> &textures)=0;
			virtual void attachDepthTexture(Texture *texture)=0;
			virtual void bind()=0;
		};
	}
}

#endif