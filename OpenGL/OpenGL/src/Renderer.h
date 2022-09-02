#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear();

    /**
     * \brief The framebuffer size function takes a GLFWwindow as its first argument and two
     * integers indicating the new window dimensions. Whenever the window changes in size,
     * GLFW calls this function and fills in the proper arguments for you to process.
     * \param window GLFWwindow 
     * \param width the width of the viewport
     * \param height the height of the viewport
     */
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
        GLCall(glViewport(0, 0, width, height));
    }

    static void EnableWireframeMode() {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }

    static void DisableWireframeMode() {
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    }
};