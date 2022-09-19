#pragma once

#include <GLFW/glfw3.h>

namespace Utils
{
    constexpr int DEFAULT_WINDOW_WIDTH = 800;
    constexpr int DEFAULT_WINDOW_HEIGHT = 600;

    extern int windowWidth;
    extern int windowHeight;

    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

}  // namespace Utils