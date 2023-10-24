#include <terrain/ChunkMesh.h>
#include <util/Log.h>
#include <chrono>


terrain::ChunkMesh::ChunkMesh(glm::ivec3 position)
	:terrain::Chunk(position)
{
	m_Vao = std::make_unique<gfx::VertexArray>();
	m_Vbo = std::make_unique<gfx::VertexBuffer>();
	m_Ibo = std::make_unique<gfx::IndexBuffer>();

	m_Vao->LinkAttrib(m_Vbo.get(), 0, GL_FLOAT, 3, GL_FALSE, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(0));
	m_Vao->LinkAttrib(m_Vbo.get(), 1, GL_FLOAT, 2, GL_FALSE, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(3 * sizeof(GLfloat)));
	m_Vao->LinkAttribi(m_Vbo.get(), 2, GL_INT, 1, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(5 * sizeof(GLfloat)));


	util::Log<glm::ivec3>(m_Position, "Chunk Created at position :");

}


void terrain::ChunkMesh::Build()
{
	
	glm::ivec3 blockPos;

	for (blockPos.x = m_Position.x; blockPos.x < this->m_Size.x+m_Position.x; blockPos.x++)
	{
		for (blockPos.y = m_Position.y; blockPos.y < this->m_Size.y+m_Position.y; blockPos.y++)
		{
			for (blockPos.z = m_Position.z; blockPos.z < this->m_Size.z+m_Position.z; blockPos.z++)
			{
				Block* currentBlock = this->getBlock(blockPos);
				if (currentBlock!=nullptr)
				{
					if (currentBlock->mesh != BLOCKMESH_NULL)
					{
						currentBlock->generateMesh(m_MeshData.indices, m_MeshData.vertices, this->getBlockNeighBours(blockPos), blockPos);
					}
				}
			}
		}
	}
	
	if ((m_MeshData.vertices.size() != 0) && (m_MeshData.indices.size() != 0))
	{
		m_Vbo->loadNewData(m_MeshData.vertices);
		m_Ibo->loadNewData(m_MeshData.indices);
	}
	else
	{
		m_Vbo->loadNewData({});
		m_Ibo->loadNewData({});
		m_IsEmpty = true;
	}

	m_IsBuild = true;
	m_ShouldRebuild = false;
}

void terrain::ChunkMesh::Render(gfx::TextureArray& textureArray, gfx::Shader& shader, glm::mat4 view, glm::mat4 projection, glm::vec4 grassColor)
{

	shader.Bind();
	shader.SetUniform4f("grassTopColor", grassColor.x, grassColor.y, grassColor.z, grassColor.w);

	shader.SetUniformMat4f("u_Model", glm::mat4(1.0f));
	shader.SetUniformMat4f("u_View", view);
	shader.SetUniformMat4f("u_Projection", projection);

	textureArray.Bind();

	m_Vao->Bind();
	m_Ibo->Bind();

	GLCall(glDrawElements(GL_TRIANGLES, m_Ibo->GetCount(), GL_UNSIGNED_INT, nullptr));

	m_Vao->UnBind();
	m_Ibo->UnBind();
	
	textureArray.UnBind();
	shader.UnBind();
}

terrain::ChunkMesh::~ChunkMesh()
{
	m_MeshData = {};
	m_Neighbours = {};
	m_Data = {};
	util::Log<glm::ivec3>(m_Position, "Chunk Destroyed at position :");
}
