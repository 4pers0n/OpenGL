#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

// struct holding source code for two shaders
struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

/// <summary>
/// Parse the shader file into a vertex shader and a fragment shader
/// </summary>
/// <param name="file_path">path to the shader file</param>
/// <returns>a struct holding two source code for the shaders</returns>
static ShaderProgramSource ParseShader(const std::string& file_path) {
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

/// <summary>
/// Compile the shader with the source code provided
/// </summary>
/// <param name="type">the shader type</param>
/// <param name="source">source code for the shader</param>
/// <returns>the shader_id if success. GL_FALSE otherwise</returns>
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int shader_id = glCreateShader(type));
    const char* src = source.c_str();
    const int length[1] = { strlen(src) };

    // change the source code for the shader
    // can be passed in as an array of pointers to char array
    GLCall(glShaderSource(shader_id, 1, &src, length));
    GLCall(glCompileShader(shader_id));
    int status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) _malloca(length * sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, message);
        std::cerr << "Failed to compile shader" << std::endl;
        std::cerr << message << std::endl;

        return GL_FALSE;
    }

    return shader_id;
}

/// <summary>
/// create a program with vertexshader and fragmentshader linked
/// </summary>
/// <param name="vertexShader">source code for vertexshader</param>
/// <param name="fragmentShader">source code for fragmentshader</param>
/// <returns>the program_id if success. GL_FALSE otherwise</returns>
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error when initializing GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // the actual data we put into the vertex buffer
    float positions[] = {
        -0.5f, -0.5f,  // each line is a vertex                          index:0
         0.5f, -0.5f,  // we group two elements in each line together    index:1
         0.5f,  0.5f,  // and it's called an attribute                   index:2
        -0.5f,  0.5f,  //                                                index:3
         0.0f,  1.0f   //                                                index:4
    };

    // index buffer (used to remove redundant vertices)
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
        2, 4, 3
    };

    VertexArray* va = new VertexArray;

    VertexBuffer* vb = new VertexBuffer(positions, 5 * 2 * sizeof(float));
    
    VertexBufferLayout* layout = new VertexBufferLayout;
    layout->Push<float>(2);
    va->AddBuffer(*vb, *layout);

    IndexBuffer* ib = new IndexBuffer(indices, 3 * 3);
    
    // Visual studio puts the working directory to ProjectDir by default in debugging mode
    // So we use "res/shaders" here instead of "../res/shaders"
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

    std::cout << "VERTEX Shader:" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT Shader:" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int program_id = CreateShader(source.VertexSource, source.FragmentSource);

    // use the prgram_id in the current rendering state
    // this tells glDrawArrays to use our shader(program) instead of
    // a default one that our gpu manufacture implemented
    GLCall(glUseProgram(program_id));

    // use this to get the location of the uniform before actually sending
    // any data to it. (each uniform will be assigned a unique location)
    GLCall(int location = glGetUniformLocation(program_id, "u_Color"));
    ASSERT(location != 1);  // CAUTION: if uniform is unused, the location will still be -1
    // use this to send the data to the uniform variable inside the shader
    // 4f means 4 floats
    GLCall(glUniform4f(location, 0.8f, 0.3f, 0.2f, 1.0f));

    // used for animation
    float r = 0.8f;
    float increment = 0.01f;

    // because va has all the information stored in it
    va->UnBind();
    ib->UnBind();
    vb->UnBind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        if (r > 1.0f) {
            increment = -0.01f;
        }
        else if (r < 0.0f) {
            increment = 0.01f;
        }
        r += increment;
        GLCall(glUniform4f(location, r, 0.3f, 0.2f, 1.0f));

        // multiple bindings here in case there are many buffers
        va->Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // use this to clean the program we created
    GLCall(glDeleteProgram(program_id));
    delete(vb);
    delete(ib);
    delete(va);
    delete(layout);
    glfwTerminate();
    return 0;
}