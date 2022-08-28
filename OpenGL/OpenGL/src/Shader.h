#pragma once
#include <string>
#include <unordered_map>

// struct holding source code for two shaders
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	// caching system for uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	int GetUniformLocation(const std::string& name);

	/// <summary>
    /// Compile the shader with the source code provided
    /// </summary>
    /// <param name="type">the shader type</param>
    /// <param name="source">source code for the shader</param>
    /// <returns>the shader_id if success. GL_FALSE otherwise</returns>
    ///
    unsigned CompileShader(unsigned type, const std::string& source);

	/// <summary>
    /// create a program with vertexshader and fragmentshader linked
    /// </summary>
    /// <param name="vertexShader">source code for vertexshader</param>
    /// <param name="fragmentShader">source code for fragmentshader</param>
    /// <returns>the program_id if success. GL_FALSE otherwise</returns>
    unsigned CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    /// <summary>
    /// Parse the shader file into a vertex shader and a fragment shader
    /// </summary>
    /// <param name="file_path">path to the shader file</param>
    /// <returns>a struct holding two source code for the shaders</returns>
	ShaderProgramSource ParseShader(const std::string& file_path);
};
