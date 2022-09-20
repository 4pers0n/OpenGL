#include "Projection.h"

#include <GLM/gtc/matrix_transform.hpp>

#include "../Utils/MainUtils.h"

namespace Maths
{
    int initialWindowWidth = Utils::DEFAULT_WINDOW_WIDTH;
    int initialWindowHeight = Utils::DEFAULT_WINDOW_HEIGHT;

    glm::mat4 GetOrthoProjMatrix(const ScaleMode mode, const int windowWidth, const int windowHeight)
    {
        if (mode == ScaleMode::AspectRatio)
        {
            float projectedWidth = 0.0f, projectedHeight = 0.0f;
            if (windowWidth < windowHeight)
            {
                projectedWidth = 2.0f;
                projectedHeight = 1.0f * windowHeight / windowWidth * 2.0f;
            }
            else
            {
                projectedHeight = 2.0f;
                projectedWidth = 1.0f * windowWidth / windowHeight * 2.0f;
            }

            const glm::mat4 proj = glm::ortho(-projectedWidth / 2, projectedWidth / 2,
            -projectedHeight / 2, projectedHeight / 2, -1.0f, 1.0f);

            return proj;
        }
        else if (mode == ScaleMode::FullScreen)
        {
            return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        }
        else
        {
            float projectedWidth = 2.0f * (1.0f * windowWidth / initialWindowWidth);
            float projectedHeight = 2.0f * (1.0f * windowHeight / initialWindowHeight);

            const glm::mat4 proj = glm::ortho(-projectedWidth / 2, projectedWidth / 2,
            -projectedHeight / 2, projectedHeight / 2, -1.0f, 1.0f);

            return proj;
        }
    }

    glm::mat4 GetPerspProjMatrix(ScaleMode mode, float fov, int windowWidth, int windowHeight)
    {
        if (mode == ScaleMode::AspectRatio)
        {
            return glm::perspective(glm::radians(fov), 1.0f * Utils::windowWidth / Utils::windowHeight, 0.1f, 100.0f);
        }
        else
        {
            return glm::perspective(glm::radians(fov), 1.0f * initialWindowWidth / initialWindowHeight, 0.1f, 100.0f);
        }
    }
}  // namespace Maths
