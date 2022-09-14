#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


Shader::Shader(const std::string& filepath)
    :m_RendererID(0), m_FilePath(filepath) {
    // Visual studio puts the working directory to ProjectDir by default in debugging mode
    // So we use "res/shaders" here instead of "../res/shaders"
    ShaderProgramSource source = ParseShader(filepath);

    std::cout << "VERTEX Shader:" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT Shader:" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    // use this to clean the program we created
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    // use the prgram_id in the current rendering state
    // this tells glDrawArrays to use our shader(program) instead of
    // a default one that our gpu manufacture implemented
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    int location = GetUniformLocation(name);
    // ASSERT(location != 1);  // CAUTION: if uniform is unused, the location will still be -1
    if (location == -1) {
        std::cout << "Warning: uniform " + name + " doesn't exist!" << std::endl;
    }
    // use this to send the data to the uniform variable inside the shader
    // 4f means 4 floats
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache.find(name)->second;
    } else {
        // use this to get the location of the uniform before actually sending
        // any data to it. (each uniform will be assigned a unique location)
        GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
        m_UniformLocationCache.insert({ name, location });
        return location;
    }
}

ShaderProgramSource Shader::ParseShader(const std::string& file_path) {
    std::ifstream stream(file_path);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != line.npos) {
            if (line.find("vertex") != line.npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != line.npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    stream.close();
    return ShaderProgramSource{ ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int shader_id = glCreateShader(type));
    const char* src = source.c_str();
    const int length[1] = { (int)strlen(src) };

    // change the source code for the shader
    // can be passed in as an array of pointers to char array
    GLCall(glShaderSource(shader_id, 1, &src, length));
    GLCall(glCompileShader(shader_id));
    int status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, message);
        std::cerr << "Failed to compile shader" << std::endl;
        std::cerr << message << std::endl;

        return GL_FALSE;
    }

    return shader_id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program_id = glCreateProgram());
    unsigned int vshader = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fshader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    GLCall(glAttachShader(program_id, vshader));
    GLCall(glAttachShader(program_id, fshader));
    GLCall(glLinkProgram(program_id));
    GLCall(glValidateProgram(program_id));
    int status;
    GLCall(glGetProgramiv(program_id, GL_VALIDATE_STATUS, &status));
    if (status != GL_TRUE) { return GL_FALSE; }

    GLCall(glDeleteShader(vshader));
    GLCall(glDeleteShader(fshader));

    return program_id;
}
