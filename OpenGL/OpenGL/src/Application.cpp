#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/// <summary>
/// Compile the shader with the source code provided
/// </summary>
/// <param name="type">the shader type</param>
/// <param name="source">source code for the shader</param>
/// <returns>the shader_id if success. GL_FALSE otherwise</returns>
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int shader_id = glCreateShader(type);
    const char* src = source.c_str();
    const int length[1] = { strlen(src) };

    // change the source code for the shader
    // can be passed in as an array of pointers to char array
    glShaderSource(shader_id, 1, &src, length);
    glCompileShader(shader_id);
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
    unsigned int program_id = glCreateProgram();
    unsigned int vshader = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fshader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program_id, vshader);
    glAttachShader(program_id, fshader);
    glLinkProgram(program_id);
    glValidateProgram(program_id);
    int status;
    glGetProgramiv(program_id, GL_VALIDATE_STATUS, &status);
    if (status != GL_TRUE) { return GL_FALSE; }

    glDeleteShader(vshader);
    glDeleteShader(fshader);

    return program_id;
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error when initializing GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // the actual data we put into the vertex buffer
    float positions[6] = {
        -0.5f, -0.5f,  // each line is a vertex
         0.0f,  0.5f,  // we group two elements in each line together
         0.5f, -0.5f   // and it's called an attribute
    };

    // create a buffer, buffer_id is the output parameter
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id);
    if (buffer_id == GL_INVALID_VALUE) {
        std::cerr << "Error when generating a buffer" << std::endl;
        glfwTerminate();
        return -1;
    }
    // bind the buffer to an array buffer inside vram
    // enter the state of having this buffer (no need to specify the buffer later)
    // (imagine seleting a layer in Photoshop)
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    // specify the data(we can specify the size first)
    // check the docs.GL for this function
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    // 1. We call this function once because we only have one attribute(position)
    // para - index : the index of this attribute
    // para - size : how many types are inside this attribute
    // para - type : the type of element inside this attribute
    // para - normalized : boolean of if to normalize the data
    // para - stride : offset to go to the next vertex
    // para - pointer : specifies an offset of the first component
    //                  of the first generic vertex attribute in the array
    //                  (the offset to an attribute)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    // used to enable the attribute above. Again state machine,
    // only need to specify the index. Can be called before the line above.
    glEnableVertexAttribArray(0);

    // actual source code for vertex shader
    // specifies the locations of vertices
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main() "
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    // actual source code for fragment shader
    // specifies which color to draw for each pixel
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main() "
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    unsigned int program_id = CreateShader(vertexShader, fragmentShader);

    // use the prgram_id in the current rendering state
    // this tells glDrawArrays to use our shader(program) instead of
    // a default one that our gpu manufacture implemented
    glUseProgram(program_id);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // actually draw the stuff stored in the vertex buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // use this to clean the program we created
    glDeleteProgram(program_id);
    glfwTerminate();
    return 0;
}