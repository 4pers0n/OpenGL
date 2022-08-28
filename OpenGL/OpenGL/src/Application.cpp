#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

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

    Shader* shader = new Shader("res/shaders/Basic.shader");
    shader->Bind();

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

        // multiple bindings here in case there are many buffers
        va->Bind();

        shader->SetUniform4f("u_Color", r, 0.3f, 0.2f, 1.0f);

        GLCall(glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    
    delete(vb);
    delete(ib);
    delete(va);
    delete(layout);
    delete(shader);
    glfwTerminate();
    return 0;
}