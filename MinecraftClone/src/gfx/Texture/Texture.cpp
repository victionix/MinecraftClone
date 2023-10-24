#include <gfx/Texture/Texture.h>
#include <stb_image/stb_image.h>




gfx::Texture::Texture(std::string& path, int unit)
    : m_Slot(unit)
{    
    stbi_set_flip_vertically_on_load(1);
    int width, height, bpp;
    auto data = stbi_load(path.c_str(), &width, &height, &bpp, 4);
    GLCall(glGenTextures(1, &m_TextureID));
    Bind();

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    if (data)
        stbi_image_free(data);
    Unbind();
}           



gfx::Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_TextureID));
}

void gfx::Texture::texUnit(Shader& shader, const std::string& uniform)
{
    shader.Bind();
    shader.SetUniform1i(uniform, m_Slot);
}

void gfx::Texture::Bind() const
{
    GLCall(glActiveTexture(GL_TEXTURE0+m_Slot))
    GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void gfx::Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D,0));
}

gfx::TextureArray::TextureArray(std::vector<std::string> paths, int unit)
    :m_Slot(unit)
{
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);

    GLCall(glGenTextures(1, &m_TextureID));
    GLCall(glActiveTexture(GL_TEXTURE0 + m_Slot))
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID);
    unsigned char* data = stbi_load(paths[0].c_str(), &widthImg, &heightImg, &numColCh, 0);

    glTextureStorage3D(m_TextureID, 1, GL_RGBA8, widthImg, heightImg, paths.size());

    glTextureSubImage3D(m_TextureID, 0, 0, 0, 0, widthImg, heightImg, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    for (int i = 1; i < paths.size(); i++)
        addTexture(paths[i], i);
    Bind();
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    UnBind();
}

gfx::TextureArray::~TextureArray()
{
    GLCall(glDeleteTextures(1, &m_TextureID));
}

void gfx::TextureArray::addTexture(std::string path, int layer)
{
    Bind();
    int widthImg, heightImg, numColCh;
    unsigned char* data = stbi_load(path.c_str(), &widthImg, &heightImg, &numColCh, 0);
    glTextureSubImage3D(m_TextureID, 0, 0, 0, layer, widthImg, heightImg, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    UnBind();
    stbi_image_free(data);
}

void gfx::TextureArray::texUnit(Shader& shader, const std::string& uniform)
{
    shader.Bind();
    shader.SetUniform1i(uniform, m_Slot);
}

void gfx::TextureArray::Bind() const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + m_Slot))
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID));
}

void gfx::TextureArray::UnBind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
}
