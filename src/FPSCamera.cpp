#include <R3D/Scene/FPSCamera.h>
#include <R3D/Core/Device.h>
#include <R3D/Core/Input.h>
#include <R3D/Core/Math.h>
#include <cmath>

namespace r3d
{
	namespace scene
	{
		FPSCamera::FPSCamera(core::Device *device)
			: m_Device(device), m_HorizontalAngle(0.0f), m_VerticalAngle(0.0f), m_MouseSpeed(3.0), m_Speed(120.0)
		{
			m_ProjMatrix = core::Perspective(45.0f*3.1415f/180.0f, 800.0f/600.0f, 1.0f, 999999.0f);
			m_LastUpdateTime = m_Device->getTime();
		}

		core::Matrix4 FPSCamera::getViewMatrix()
		{
			return m_ViewMatrix;
		}

		core::Matrix4 FPSCamera::getProjectionMatrix()
		{
			return m_ProjMatrix;
		}

		void FPSCamera::update()
		{
			core::Input *input = m_Device->getInput();
			double xpos, ypos;
			input->getMousePosition(&xpos, &ypos);

			float delta_time = m_Device->getTime() - m_LastUpdateTime;

			// TODO: DONT HARD CODE THIS
			m_HorizontalAngle += m_MouseSpeed * delta_time * float(800.0/2.0 - xpos );
			m_VerticalAngle   += m_MouseSpeed * delta_time * float(600.0/2.0 - ypos );

			m_Dir = core::Vector3f(
				std::cos(m_VerticalAngle)*std::sin(m_HorizontalAngle),
    			std::sin(m_VerticalAngle),
   				std::cos(m_VerticalAngle)*std::cos(m_HorizontalAngle));

			core::Vector3f right = core::Vector3f(
	    		std::sin(m_HorizontalAngle - 3.14159/2.0),
	    		0,
	    		std::cos(m_HorizontalAngle - 3.14159/2.0));
			m_Up = core::Cross(right, m_Dir);
		////////////////////////////////////////////////////

			
			if (input->isKeyHold(core::KeyCode::KEY_UP))
				m_Pos += m_Dir * delta_time * m_Speed;
			
			// Move backward
			if (input->isKeyHold(core::KeyCode::KEY_DOWN))
			    m_Pos -= m_Dir * delta_time * m_Speed;
			
			// Strafe right
			if (input->isKeyHold(core::KeyCode::KEY_RIGHT))
			    m_Pos += right * delta_time * m_Speed;
			
			// Strafe left
			if (input->isKeyHold(core::KeyCode::KEY_LEFT))
			    m_Pos -= right * delta_time * m_Speed;

			m_ViewMatrix = core::LookAt(m_Pos, m_Pos+m_Dir, m_Up);

			m_LastUpdateTime = m_Device->getTime();

			//fprintf(stderr, "%f %f %f\n", m_Pos.x, m_Pos.y, m_Pos.z);

			input->setMousePosition(800/2.0, 600/2.0);
		}

		void FPSCamera::setPosition(const core::Vector3f &pos)
		{
			m_Pos = pos;
		}
	}
}