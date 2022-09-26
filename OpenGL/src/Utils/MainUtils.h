#pragma once

#include <GLFW/glfw3.h>

#include "../Maths/View.h"

namespace Utils
{
    constexpr int DEFAULT_WINDOW_WIDTH = 800;
    constexpr int DEFAULT_WINDOW_HEIGHT = 600;
    constexpr int DEFAULT_MAJOR_VERSION = 3;
    constexpr int DEFAULT_MINOR_VERSION = 3;

    // Dynamically updated variables that store the actual width and height of the window
    extern int windowWidth;
    extern int windowHeight;

    // Stores the delta time between each frames
    extern float deltaTime;

    // Stores a pointer to the camera that will be used
    extern Maths::ViewMatrix* camera;

    // Stores the current field of view value
    extern float fieldOfView;

    /**
     * \brief Change the glViewPort based on new width and height.
     *  Should be called whenever there is a window resize
     * \param window GLFWwindow pointer
     * \param width The width of the new window
     * \param height The height of the new window
     */
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    /**
     * \brief Change the camera based on mouse movement
     * \param window GLFWwindow pointer
     * \param xPosIn The x axis value of the cursor
     * \param yPosIn The y axis value of the cursor
     */
    void MouseMovementCallback(GLFWwindow* window, double xPosIn, double yPosIn);

    /**
     * \brief Change the cursor state based on mouse button click
     * \param window GLFWwindow pointer
     * \param button Which mouse button is clicked
     * \param action Which is the action if the click(press or release)
     * \param mods Modifications
     */
    void MouseButtonClickCallback(GLFWwindow* window, int button, int action, int mods);

    void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    /**
     * \brief Process user input like key press and mouse click
     * \param window GLFWwindow pointer
     */
    void ProcessInput(GLFWwindow* window);

    /**
     * \brief Update the camera variable
     * \param newCamera Used to update
     */
    inline void UpdateCamera(Maths::ViewMatrix* newCamera) { camera = newCamera; }

}  // namespace Utils