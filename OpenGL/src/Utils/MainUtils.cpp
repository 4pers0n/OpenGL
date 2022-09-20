#include "GLDebugHelper.h"

#include "MainUtils.h"

namespace Utils
{
    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;

    void FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
    {
        windowWidth = width;
        windowHeight = height;
        GLCall(glViewport(0, 0, width, height));
    }

    void ProcessInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }
}  // namespace Utils