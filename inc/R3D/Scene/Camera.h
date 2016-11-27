#ifndef _R3D_SCENE_CAMERA_H_
#define _R3D_SCENE_CAMERA_H_	

#include <R3D/Core/Math.h>

namespace r3d
{
	namespace scene
	{
		class Camera
		{
		public:
			virtual ~Camera(){}
			virtual core::Matrix4 getViewMatrix()=0;
			virtual core::Matrix4 getProjectionMatrix()=0;
			virtual void update()=0;
			virtual void setPosition(const core::Vector3f &pos)=0;
		};
	}
}

#endif