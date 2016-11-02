#ifndef _R3D_SCENE_GLMESH_H_
#define _R3D_SCENE_GLMESH_H_	

#include <R3D/Scene/Mesh.h>
#include <GL/glew.h>
#include <cstdint>

namespace r3d
{
	namespace scene
	{
		class GLMesh: public Mesh
		{
		public:
			GLMesh();
			virtual ~GLMesh();
			virtual void draw() override;
			virtual void load(const std::vector<core::Vertex> &vertices, const std::vector<uint32_t> &indices) override;
			virtual void load(const std::vector<core::Vertex> &vertices) override;

			virtual bool hasUV() override;
			virtual bool hasNormal() override;
		private:
			// store vertex array
			GLuint m_Id;
			GLuint m_BufferId;
			GLuint m_IndicesId;

			uint32_t m_NumIndices;
			uint32_t m_NumVertices;
		};
	}
}

#endif