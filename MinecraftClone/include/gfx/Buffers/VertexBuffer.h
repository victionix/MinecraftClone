#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <gfx/Debug/Debug.h>
#include <vector>
#include <gfx/Vertex/Vertex.h>

namespace gfx {
    class VertexBuffer
    {
    public:
        VertexBuffer(std::vector<Vertex> vertices);
        VertexBuffer();
        ~VertexBuffer();

        void loadNewData(std::vector<Vertex> newVertices);

        void Bind() const;
        void Unbind() const;

    public:
        unsigned int m_RendererID;
    };
}
#endif