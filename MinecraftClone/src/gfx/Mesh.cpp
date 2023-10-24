#include <gfx/Mesh.h>

namespace gfx {
	Mesh::Mesh(MeshData& data)
	{
		
		m_Vao.LinkAttrib(m_Vbo, 0, GL_FLOAT, 3, GL_FALSE, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(0));
		m_Vao.LinkAttrib(m_Vbo, 1, GL_FLOAT, 2, GL_FALSE, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(3 * sizeof(GLfloat)));
		m_Vao.LinkAttribi(m_Vbo, 2, GL_INT, 1, 5 * sizeof(GLfloat) + sizeof(GLuint), (void*)(5 * sizeof(GLfloat)));

		m_Ibo.loadNewData(data.indices);
		m_Vbo.loadNewData(data.vertices);

	}

	Mesh::~Mesh()
	{
		m_Ibo.~IndexBuffer();
		m_Vao.~VertexArray();
		m_Vbo.~VertexBuffer();
	}

	Mesh::Mesh(Mesh&& other) noexcept
	{
		m_Vao = other.m_Vao;
		m_Vbo = other.m_Vbo;
		m_Ibo = other.m_Ibo;
	}

	unsigned int Mesh::getVertexCount()
	{
		return m_Ibo.GetCount();
	}
	void Mesh::Bind()
	{
		m_Ibo.Bind();
		m_Vao.Bind();
	}

	void Mesh::UnBind()
	{
		m_Ibo.UnBind();
		m_Vao.UnBind();
	}

}