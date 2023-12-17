#include <gfx/Buffers/IndexBuffer.h>
#include <util/Log.h>

gfx::IndexBuffer::IndexBuffer(std::vector<uint32_t> indices)
    :
    m_Count(indices.size())
{
    GLCall(glGenBuffers(1, &m_RendererID));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW));
    UnBind();

}

gfx::IndexBuffer::IndexBuffer()
    :m_Count(0)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    Bind();
    UnBind();
}

gfx::IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void gfx::IndexBuffer::loadNewData(std::vector<uint32_t> newIndices)
{
    Bind();
    m_Count = newIndices.size();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, newIndices.size() * sizeof(uint32_t), newIndices.data(), GL_STATIC_DRAW));
    UnBind();
}

void gfx::IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void gfx::IndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}