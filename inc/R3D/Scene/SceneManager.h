#ifndef _R3D_SCENE_SCENEMANAGER_H_
#define _R3D_SCENE_SCENEMANAGER_H_

#include <map>
#include <string>

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
		private:
			core::Device *m_Device;
			std::map<std::string, Mesh *> m_Objects;
		};
	}
}

#endif