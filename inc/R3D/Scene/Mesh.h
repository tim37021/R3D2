#ifndef _R3D_SCENE_MESH_H_
#define _R3D_SCENE_MESH_H_

namespace r3d
{
	class rendering::ShaderProgram;
	namespace scene
	{
		class Mesh
		{
		public:

			virtual void draw()=0;
		private:
			rendering::ShaderProgram m_Program;
		};
	}
}

#endif