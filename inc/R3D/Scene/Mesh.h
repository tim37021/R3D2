#ifndef _R3D_SCENE_MESH_H_
#define _R3D_SCENE_MESH_H_

#include <R3D/Core/Math.h>
#include <vector>
#include <cstdint>

namespace r3d
{
	namespace scene
	{
		class Mesh
		{
		public:
			virtual ~Mesh()=default;
			virtual void draw()=0;
			virtual void load(const std::vector<core::Vertex> &vertices, const std::vector<uint32_t> &indices)=0;
			virtual void load(const std::vector<core::Vertex> &vertices)=0;

			virtual bool hasUV()=0;
			virtual bool hasNormal()=0;
		};
	}
}

#endif