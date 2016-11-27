#include "GLMesh.h"

namespace r3d
{
	namespace scene
	{
		GLMesh::GLMesh()
			: m_NumIndices(0), m_NumVertices(0)
		{
			glGenVertexArrays(1, &m_Id);
		}

		GLMesh::~GLMesh()
		{
			glDeleteVertexArrays(1, &m_Id);
			if(m_NumVertices>0) {
				glDeleteBuffers(1, &m_BufferId);
			}
			if(m_NumIndices>0) {
				glDeleteBuffers(1, &m_BufferId);
				glDeleteBuffers(1, &m_IndicesId);
			}
		}

		void GLMesh::draw()
		{
			glBindVertexArray(m_Id);
			if(m_NumIndices>0)
				glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, nullptr);
			if(m_NumVertices>0)
				glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);
		}

		void GLMesh::load(const std::vector<core::Vertex> &vertices, const std::vector<uint32_t> &indices)
		{
			glGenBuffers(1, &m_BufferId);
			glGenBuffers(1, &m_IndicesId);

			glBindVertexArray(m_Id);

			glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
			glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(core::Vertex), vertices.data(), GL_STATIC_DRAW);
			
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), reinterpret_cast<const GLvoid* >(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), reinterpret_cast<const GLvoid* >(sizeof(core::Vector3f)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), reinterpret_cast<const GLvoid* >(sizeof(core::Vector3f)+sizeof(core::Vector2f)));
	
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
			m_NumIndices = indices.size();
			m_NumVertices = 0;
		}

		void GLMesh::load(const std::vector<core::Vertex> &vertices)
		{
			glGenBuffers(1, &m_BufferId);

			glBindVertexArray(m_Id);

			glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
			glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(core::Vertex), vertices.data(), GL_STATIC_DRAW);
			
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), reinterpret_cast<const GLvoid* >(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), reinterpret_cast<const GLvoid* >(sizeof(core::Vector3f)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(core::Vertex), reinterpret_cast<const GLvoid* >(sizeof(core::Vector3f)+sizeof(core::Vector2f)));
	
			m_NumVertices = vertices.size();
			m_NumIndices = 0;
		}

		bool GLMesh::hasUV()
		{
			return true;
		}
		bool GLMesh::hasNormal()
		{
			return true;
		}
	}
}