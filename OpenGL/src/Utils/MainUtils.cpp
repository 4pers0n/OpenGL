#include "GLDebugHelper.h"

#include "MainUtils.h"

namespace Utils
{
    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;

    float deltaTime = 0.0f;

    Maths::ViewMatrix* camera = nullptr;

    void FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
    {
        windowWidth = width;
        windowHeight = height;
        GLCall(glViewport(0, 0, width, height));
    }

    void MouseMovementCallback(GLFWwindow* window, const double xPosIn, const double yPosIn)
    {
        static bool firstMouse = true;

        static float lastX = windowWidth / 2;
        static float lastY = windowHeight / 2;

        const auto xPos = static_cast<float>(xPosIn);
        const auto yPos = static_cast<float>(yPosIn);

        if (firstMouse)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        const float xoffset = lastX - xPos;
        const float yoffset = lastY - yPos;

        lastX = xPos;
        lastY = yPos;

        camera->LookAround(xoffset, yoffset);
    }

    void MouseButtonClickCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    void ProcessInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->Move(Maths::Forward, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->Move(Maths::Backward, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->Move(Maths::Left, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->Move(Maths::Right, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera->Move(Maths::Up, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera->Move(Maths::Down, deltaTime);
    }

}  // namespace Utils