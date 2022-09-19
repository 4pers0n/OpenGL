#pragma once

#include <string>
#include <unordered_map>

#include <GLM/glm.hpp>

namespace GLBasics
{
    /**
     * \brief A Shader class that manages creating, compiling, binding shaders and
     * provides helpers functions to manipulate uniforms
     */
    class Shader
    {
    private:
        unsigned int m_RendererID;
        mutable std::unordered_map<std::string, int> m_UniformLocationMap;  // caching for uniforms

    public:
        /**
         * \brief Constructs a Shader class and create, compile, bind vertex
         * and fragment shaders
         * \param vertexShaderPath The path to the vertex shader source file
         * \param fragmentShaderPath The path to the fragment shader source file
         */
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        /**
         * \brief Calls the underlying OpenGL functions to delete the shader program
         */
        ~Shader();

        /**
         * \brief Bind this shader program
         */
        void Bind() const;

        /**
         * \brief Unbind this Shader program
         */
        void UnBind() const;

        /**
         * \brief Set the uniform bound to this shader program
         * \param uniformName Name of the uniform
         * \param value One single integer that is used to set the uniform
         */
        void SetUniform1i(const std::string& uniformName, int value) const;

        /**
         * \brief Set the uniform bound to this shader program
         * \param uniformName Name of the uniform
         * \param v0 Values for the uniform
         * \param v1 Values for the uniform
         * \param v2 Values for the uniform
         * \param v3 Values for the uniform
         */
        void SetUniform4f(const std::string& uniformName, float v0, float v1, float v2, float v3) const;

        /**
         * \brief Set the uniform bound to this shader program
         * \param uniformName Name of the uniform
         * \param matrix A glm::mat4 object that is used to set the uniform
         */
        void SetUniformMat4f(const std::string& uniformName, const glm::mat4& matrix) const;

    private:
        // Retrieves uniform location from glProgram
        int GetUniformLocation(const std::string& uniformName) const;

        // Compiles a shader of the given type and source code
        // Returns the shader identifier
        unsigned int CompileShader(unsigned int type, std::string& shaderSource) const;

        // Attaches and link both shaders
        // Returns the program identifier
        unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader) const;

        // Read the plain string from the given file path and return it
        std::string ParseShader(const std::string& filePath) const;

    };  // class Shader
}  // namespace GLBasics
