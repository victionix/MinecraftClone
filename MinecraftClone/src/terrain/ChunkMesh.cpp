#include <terrain/ChunkMesh.h>
#include <util/Log.h>
#include <chrono>


gfx::ChunkMeshBuffers::ChunkMeshBuffers()
{
	m_Vao.LinkAttrib(m_Vbo, 0, GL_FLOAT, 3, GL_FALSE, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(0));
	m_Vao.LinkAttrib(m_Vbo, 1, GL_FLOAT, 2, GL_FALSE, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(3 * sizeof(GLfloat)));
	m_Vao.LinkAttribi(m_Vbo, 2, GL_INT, 1, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(5 * sizeof(GLfloat)));
	m_Vao.UnBind();
}


gfx::ChunkMeshBuffers::~ChunkMeshBuffers()
{
	m_Vao.~VertexArray();
	m_Vbo.~VertexBuffer();
	m_Ibo.~IndexBuffer();
}

void gfx::ChunkMeshBuffers::Bind()
{
	m_Vao.Bind();
	m_Ibo.Bind();
}


void gfx::ChunkMeshBuffers::UnBind()
{
	m_Vao.UnBind();
	m_Ibo.UnBind();
}

void gfx::ChunkMeshBuffers::LoadData(MeshData meshData)
{
	m_Vbo.loadNewData(meshData.vertices);
	m_Ibo.loadNewData(meshData.indices);
}

unsigned int gfx::ChunkMeshBuffers::getCount()
{
	return m_Ibo.GetCount();
}
terrain::ChunkMesh::ChunkMesh(glm::ivec3 position)
	:terrain::Chunk(position)
{	
	util::Log<glm::ivec3>(m_Position, "Chunk Created at position :");
}


void terrain::ChunkMesh::Build()
{
	util::Log<glm::ivec3>(m_Position, "Chunk Builded at position :");
	m_MeshData.vertices.clear();
	m_MeshData.indices.clear();

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
						
						currentBlock->generateMesh(m_MeshData,this->getBlockNeighBours(blockPos), blockPos);
					}
				}
			}
		}
	}

	if ((m_MeshData.vertices.size() != 0) && (m_MeshData.indices.size() != 0))
	{
		
		m_Buffers.LoadData(m_MeshData);
	}
	else
	{	
		m_Buffers.LoadData({});
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

	m_Buffers.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, m_Buffers.getCount(), GL_UNSIGNED_INT, nullptr));

	m_Buffers.UnBind();
	
	textureArray.UnBind();
	shader.UnBind();
}

terrain::ChunkMesh::~ChunkMesh()
{
	m_MeshData.vertices.clear();
	m_MeshData.indices.clear();
	m_Buffers.~ChunkMeshBuffers();
	util::Log<glm::ivec3>(m_Position, "Chunk Destroyed at position :");
}


