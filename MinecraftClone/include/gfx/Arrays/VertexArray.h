#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <gfx/Debug/Debug.h>
#include <gfx/Buffers/VertexBuffer.h>
#include <memory>


namespace gfx {
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void LinkAttrib(const gfx::VertexBuffer& vb, unsigned int id, unsigned int type, unsigned int count, unsigned char normalized, unsigned int stride, void* offset);
        void LinkAttribi(const gfx::VertexBuffer& vb, unsigned int id, unsigned int type, unsigned int count, unsigned int stride, void* offset);

        void LinkAttrib(const gfx::VertexBuffer* vb, unsigned int id, unsigned int type, unsigned int count, unsigned char normalized, unsigned int stride, void* offset);
        void LinkAttribi(const gfx::VertexBuffer* vb, unsigned int id, unsigned int type, unsigned int count, unsigned int stride, void* offset);

        void Bind() const;
        void UnBind() const;

    private:
        unsigned int m_RendererID;

    };
}
#endif