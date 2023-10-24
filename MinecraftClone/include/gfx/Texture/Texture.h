#ifndef TEXTURE_H
#define TEXTURE_H

#include <gfx/Debug/Debug.h>
#include <gfx/Shaders/Shader.h>
namespace gfx {
    class Texture
    {
    private:
        unsigned int m_TextureID;
        int m_Slot;
    public:
        Texture(std::string& path, int unit);
        ~Texture();
        void texUnit(Shader& shader, const std::string& uniform);
        void Bind() const;
        void Unbind() const;
    };

    class TextureArray
    {
    private:
        unsigned int m_TextureID;
        int m_Slot;
    public:
        TextureArray(std::vector<std::string> paths, int unit);
        ~TextureArray();
        void addTexture(std::string path, int layer);
        void texUnit(Shader& shader, const std::string& uniform);
        void Bind() const;
        void UnBind() const;
    };
}
#endif