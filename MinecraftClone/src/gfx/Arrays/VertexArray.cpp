#include <gfx/Arrays/VertexArray.h>
#include <util/Log.h>
gfx::VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
    Bind();
    UnBind();
}

gfx::VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void gfx::VertexArray::LinkAttrib(const gfx::VertexBuffer& vb, unsigned int id, unsigned int type, unsigned int count, unsigned char normalized, unsigned int stride, void* offset)
{
    Bind();
    vb.Bind();

    GLCall(glVertexAttribPointer(id, count, type, normalized, stride, offset));
    GLCall(glEnableVertexAttribArray(id));

    UnBind();
    vb.Unbind();
}

void gfx::VertexArray::LinkAttribi(const gfx::VertexBuffer& vb, unsigned int id, unsigned int type, unsigned int count, unsigned int stride, void* offset)
{
    Bind();
    vb.Bind();

    GLCall(glVertexAttribIPointer(id, count, type, stride, offset));
    GLCall(glEnableVertexAttribArray(id));


    UnBind();
    vb.Unbind();
}

void gfx::VertexArray::LinkAttrib(const gfx::VertexBuffer* vb, unsigned int id, unsigned int type, unsigned int count, unsigned char normalized, unsigned int stride, void* offset)
{
    Bind();
    vb->Bind();

    GLCall(glVertexAttribPointer(id, count, type, normalized, stride, offset));
    GLCall(glEnableVertexAttribArray(id));

    UnBind();
    vb->Unbind();
}

void gfx::VertexArray::LinkAttribi(const gfx::VertexBuffer* vb, unsigned int id, unsigned int type, unsigned int count, unsigned int stride, void* offset)
{
    Bind();
    vb->Bind();

    GLCall(glVertexAttribIPointer(id, count, type, stride, offset));
    GLCall(glEnableVertexAttribArray(id));


    UnBind();
    vb->Unbind();
}

void gfx::VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}
void gfx::VertexArray::UnBind() const
{
    GLCall(glBindVertexArray(0));
}