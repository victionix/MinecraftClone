#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <gfx/gfx.h>
#include <gfx/Mesh.h>
#include <terrain/Chunk.h>


namespace gfx
{
	class ChunkMeshBuffers
	{
	public:
		ChunkMeshBuffers(MeshData meshData);
		~ChunkMeshBuffers();
		void Bind();
		void UnBind();
		unsigned int  getCount();
	private:
		gfx::VertexArray m_Vao;
		gfx::VertexBuffer m_Vbo;
		gfx::IndexBuffer m_Ibo;
	};
}


namespace terrain
{
	class ChunkMesh : public terrain::Chunk{
	public:
		ChunkMesh(glm::ivec3 position);
		ChunkMesh(ChunkMesh const&) = delete;
		ChunkMesh& operator=(ChunkMesh const&) = delete;
		
		~ChunkMesh();

		void Build();
		void Render(gfx::TextureArray& textureArray, gfx::Shader& shader,glm::mat4 view, glm::mat4 projection, glm::vec4 grassColor);

	private:
		std::unique_ptr<gfx::ChunkMeshBuffers> m_Buffers;
		MeshData m_MeshData;
	public:
		bool m_IsBuild = false;
		bool m_ShouldRebuild = false;
		bool m_IsEmpty = false;
	};

}


#endif