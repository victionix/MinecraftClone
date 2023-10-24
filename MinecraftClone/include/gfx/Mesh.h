#ifndef MESH_H
#define MESH_H

#include <gfx/gfx.h>

struct MeshData
{
	std::vector<uint32_t> indices = {};
	std::vector<Vertex> vertices = {};
};

namespace gfx {

	class Mesh
	{
	public:
		Mesh(MeshData& data);

		~Mesh();

		Mesh(Mesh const&) = delete;
		Mesh& operator=(Mesh const&) = delete;

		Mesh(Mesh&& other) noexcept;

		unsigned int	 getVertexCount();

		void Bind();
		void UnBind();

	private:
		gfx::IndexBuffer m_Ibo;
		gfx::VertexBuffer m_Vbo;
		gfx::VertexArray m_Vao;
	};
}

#endif