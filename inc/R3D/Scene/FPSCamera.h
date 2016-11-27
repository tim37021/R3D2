#ifndef _R3D_SCENE_FPSCAMERA_H_
#define _R3D_SCENE_FPSCAMERA_H_	

#include <R3D/Scene/Camera.h>
#include <R3D/Core/Math.h>

namespace r3d
{
	namespace core
	{
		class Device;
	}
	
	namespace scene
	{
		class FPSCamera: public Camera
		{
		public:
			FPSCamera(core::Device *);
			virtual ~FPSCamera(){}
			virtual core::Matrix4 getViewMatrix() override final;
			virtual core::Matrix4 getProjectionMatrix() override final;
			virtual void update() override final;
			virtual void setPosition(const core::Vector3f &pos) override final;
		private:
			core::Device *m_Device;
			core::Matrix4 m_ProjMatrix, m_ViewMatrix;
			core::Vector3f m_Dir, m_Up, m_Pos;
			float m_LastUpdateTime;
			float m_HorizontalAngle, m_VerticalAngle;
			float m_MouseSpeed, m_Speed;
		};
	}
}

#endif