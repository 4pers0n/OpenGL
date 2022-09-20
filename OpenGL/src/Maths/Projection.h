# pragma once

#include <GLM/glm.hpp>

namespace Maths
{
    /**
	 * \brief Specifies which scaling mode to use
	 */
	enum ScaleMode
	{
	    AspectRatio, FullScreen, NoScaling
	};

	// Specifies the window size when the rendering starts
	extern int initialWindowWidth;
	extern int initialWindowHeight;

    /**
	 * \brief Get a scaling matrix based on the current window size
	 * \param mode A ScaleMode enum specifies which scaling mode to use
	 * \param windowWidth The width of the current window
	 * \param windowHeight The height of the current window
	 * \return A glm::mat4 which is used as a projection matrix
	 */
	glm::mat4 GetScaleMatrix(ScaleMode mode, int windowWidth, int windowHeight);

}  // namespace Maths