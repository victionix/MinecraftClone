#include <gfx/Buffers/VertexBuffer.h>

#include<iostream>

gfx::VertexBuffer::VertexBuffer(std::vector<Vertex> vertices)
{
    GLCall(glGenBuffers(1,&m_RendererID));
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
    Unbind();
}

gfx::VertexBuffer::VertexBuffer()
{
    GLCall(glGenBuffers(1, &m_RendererID));
    Bind();
    GLsizeiptr size = 0;
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW));
    Unbind();
}

gfx::VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1,&m_RendererID));
}

void gfx::VertexBuffer::loadNewData(std::vector<Vertex> newVertices)
{
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, newVertices.size()*sizeof(Vertex), newVertices.data(), GL_STATIC_DRAW));
    Unbind();


}

void gfx::VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));
}

void gfx::VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}