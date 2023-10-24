#ifndef SHADER_H
#define SHADER_H

#include <string>  
#include <unordered_map> 
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>
#include <gfx/Debug/Debug.h>

namespace gfx {
    class Shader
    {
    private:
        unsigned int m_RendererID;

    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        void SetUniform1i(const std::string& name, int value);
        void SetUniform1iv(const std::string& name, int values[]);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
        int GetUniformLocation(const std::string& name);
    private:
        void CheckCompileError(GLuint shader, std::string type);



    };
}

#endif
