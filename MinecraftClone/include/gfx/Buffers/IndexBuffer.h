#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <gfx/Debug/Debug.h>
#include <vector>

namespace gfx {
    class IndexBuffer
    {
    public:
        IndexBuffer(std::vector<uint32_t> indices);
        IndexBuffer();
        ~IndexBuffer();

        void loadNewData(std::vector<uint32_t> newIndices);
        void Bind() const;
        void UnBind() const;

        inline unsigned int GetCount() const { return m_Count; }

    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    };
}

#endif