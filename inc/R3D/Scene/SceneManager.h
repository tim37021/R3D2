#ifndef _R3D_SCENE_SCENEMANAGER_H_
#define _R3D_SCENE_SCENEMANAGER_H_

#include <map>
#include <string>
#include <R3D/Scene/FPSCamera.h>

namespace r3d
{
	namespace core
	{
		class Device;
	}
	namespace scene
	{
		class Mesh;
		class SceneManager
		{
		public:
			SceneManager(core::Device *);
			~SceneManager();
			void loadWavefrontAsync(const std::string &filename);
			void update();
			void drawAll();

			Camera *getCamera()
			{ return &m_Camera; }
		private:
			core::Device *m_Device;
			FPSCamera m_Camera;
			std::map<std::string, Mesh *> m_Objects;
		};
	}
}

#endif