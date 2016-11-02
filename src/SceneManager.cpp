#include <R3D/Scene/SceneManager.h>
#include <R3D/Core/Device.h>
#include <R3D/Core/TaskScheduler.h>
#include "GLMesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader.h"

namespace r3d
{
	namespace scene
	{
		SceneManager::SceneManager(core::Device *device)
			: m_Device(device)
		{

		}

		SceneManager::~SceneManager()
		{
			for(auto obj: m_Objects)
				delete obj.second;
		}

		void SceneManager::loadWavefrontAsync(const std::string &filename)
		{
			SceneManager *me = this;
			m_Device->getTaskScheduler()->getThreadPool().enqueue([me, filename]() {
				std::vector<tinyobj::shape_t> shapes;
				std::vector<tinyobj::material_t> materials;
				std::string err;
				tinyobj::attrib_t attrib;
				bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());
				int32_t count = 0;
				if(ret) {
					for(auto &shape: shapes) {
						std::vector<core::Vertex> *vertices = new std::vector<core::Vertex>();
						// TODO: indices drawing
						uint32_t index_offset = 0;
						for(uint32_t f=0; f<shape.mesh.num_face_vertices.size(); f++) {
							uint32_t fv = shape.mesh.num_face_vertices[f];

							for(uint32_t vv=0; vv<fv; vv++) {
								//fprintf(stderr, "%s\n", shape.name.c_str());
								tinyobj::index_t idx = shape.mesh.indices[index_offset+vv];
								core::Vertex v;
								v.m_Pos = {attrib.vertices[3*idx.vertex_index+0], attrib.vertices[3*idx.vertex_index+1], attrib.vertices[3*idx.vertex_index+2]};
								if(idx.texcoord_index!=-1)
									v.m_TexCoord = {attrib.texcoords[2*idx.texcoord_index+0], attrib.texcoords[2*idx.texcoord_index+1]};
								if(idx.normal_index!=-1)
									v.m_Normal = {attrib.normals[3*idx.normal_index+0], attrib.normals[3*idx.normal_index+1], attrib.normals[3*idx.normal_index+2]};
								vertices->push_back(v);
							}

							index_offset += fv;
						}

						std::string obj_name = shape.name;
						// capture everything would be terrible
						me->m_Device->getTaskScheduler()->scheduleTask(NORMAL_PRIORITY-count, [vertices, me, obj_name](){
							GLMesh *mesh = new GLMesh();
							mesh->load(*vertices);
							delete vertices;
							me->m_Objects[obj_name] = mesh;
							fprintf(stderr, "%s is added to the scene\n", obj_name.c_str());
						});
						count++;
					}
				}
				me->m_Device->getTaskScheduler()->scheduleTask(NORMAL_PRIORITY-count, [filename](){
					fprintf(stderr, "%s is loaded successfully\n", filename.c_str());
				});
			});
		}
	}
}