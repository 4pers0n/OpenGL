#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GLM/gtc/type_ptr.hpp>

#include "../Utils/GLDebugHelper.h"

namespace GLBasics
{
    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        : m_RendererID(0)
    {
        std::string vertexShaderSource = ParseShader(vertexShaderPath);
        std::string fragmentShaderSource = ParseShader(fragmentShaderPath);
        const unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        const unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        m_RendererID = CreateProgram(vertexShader, fragmentShader);
        GLCall(glUseProgram(m_RendererID));
    }

    Shader::~Shader()
    {
        GLCall(glDeleteProgram(m_RendererID));
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(m_RendererID));
    }

    void Shader::UnBind() const
    {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string& uniformName, int value) const
    {
        GLCall(glUniform1i(GetUniformLocation(uniformName), value));
    }

    void Shader::SetUniform4f(const std::string& uniformName, float v0, float v1, float v2, float v3) const
    {
        GLCall(glUniform4f(GetUniformLocation(uniformName), v0, v1, v2, v3));
    }

    void Shader::SetUniformMat4f(const std::string& uniformName, const glm::mat4& matrix) const
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    int Shader::GetUniformLocation(const std::string& uniformName) const
    {
        if (m_UniformLocationMap.find(uniformName) != m_UniformLocationMap.end())
        {
            return m_UniformLocationMap[uniformName];
        }
        else
        {
            GLCall(int location = glGetUniformLocation(m_RendererID, uniformName.c_str()));
            m_UniformLocationMap.insert({ uniformName, location });
            return location;
        }
    }

    unsigned Shader::CompileShader(unsigned type, std::string& shaderSource) const
    {
        GLCall(const unsigned int shaderID = glCreateShader(type));
        const char* src = shaderSource.c_str();
        GLCall(glShaderSource(shaderID, 1, &src, nullptr));
        GLCall(glCompileShader(shaderID));

        int success;
        char infoLog[1024];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }

        return shaderID;
    }

    unsigned Shader::CreateProgram(unsigned vertexShader, unsigned fragmentShader) const
    {
        GLCall(const unsigned int programID = glCreateProgram());
        GLCall(glAttachShader(programID, vertexShader));
        GLCall(glAttachShader(programID, fragmentShader));
        GLCall(glLinkProgram(programID));
        GLCall(glValidateProgram(programID));

        int success;
        char infoLog[1024];
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(programID, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }

        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));

        return programID;
    }

    std::string Shader::ParseShader(const std::string& filePath) const
    {
        std::ifstream shaderFile;
        std::stringstream shaderStream;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            shaderFile.open(filePath);
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }

        return shaderStream.str();
    }
}  // namespace GLBasics
