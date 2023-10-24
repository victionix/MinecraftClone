#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <gfx/gfx.h>
#include <gfx/Mesh.h>
#include <terrain/Chunk.h>



namespace terrain
{
	class ChunkMesh : public terrain::Chunk{
	public:
		ChunkMesh(glm::ivec3 position);
		
		~ChunkMesh();

		void Build();
		void Render(gfx::TextureArray& textureArray, gfx::Shader& shader,glm::mat4 view, glm::mat4 projection, glm::vec4 grassColor);

	private:
		std::unique_ptr<gfx::VertexArray> m_Vao;
		std::unique_ptr<gfx::VertexBuffer> m_Vbo;
		std::unique_ptr<gfx::IndexBuffer> m_Ibo;
		MeshData m_MeshData;
	public:
		bool m_IsBuild = false;
		bool m_ShouldRebuild = false;
		bool m_IsEmpty = false;
	};

}


#endif