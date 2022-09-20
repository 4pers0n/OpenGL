#pragma once

#include <GLFW/glfw3.h>

namespace Utils
{
    constexpr int DEFAULT_WINDOW_WIDTH = 800;
    constexpr int DEFAULT_WINDOW_HEIGHT = 600;
    constexpr int DEFAULT_MAJOR_VERSION = 3;
    constexpr int DEFAULT_MINOR_VERSION = 3;

    // Dynamically updated variables that store the actual width and height of the window
    extern int windowWidth;
    extern int windowHeight;

    /**
     * \brief Change the glViewPort based on new width and height.
     *  Should be called whenever there is a window resize
     * \param window GLFWwindow pointer
     * \param width The width of the new window
     * \param height The height of the new window
     */
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    /**
     * \brief Process user input like key press and mouse click
     * \param window GLFWwindow pointer
     */
    void ProcessInput(GLFWwindow* window);

}  // namespace Utils