#pragma once

#include "GLBasics/VertexBuffer.h"
#include "GLBasics/VertexArray.h"
#include "GLBasics/Shader.h"

using GLBasics::VertexBuffer;
using GLBasics::VertexArray;
using GLBasics::Shader;

/**
 * \brief Handles all the draw calls and clearing the buffer
 */
class Renderer
{
public:
    /**
	 * \brief Draw with VertexBuffer only
	 * \param mode An enum specifies the mode for this draw call
	 * \param vb The VertexBuffer that contains all the vertices data
	 * \param shader Shader program that will be used for this draw call
	 * \param numTriangles The number of triangles to the drawn
	 */
	void DrawArrays(unsigned int mode, const VertexBuffer& vb, const Shader& shader, unsigned int numTriangles);

    /**
	 * \brief Draw with VertexArray
	 * \param mode An enum specifies the mode for this draw call
	 * \param va The VertexArray that contains all the vertices data and indices data
	 * \param shader Shader program that will be used for this draw call
	 * \param numIndices The number of unsigned int inside the IndexBuffer bound to the VertexArray
	 */
	void DrawElements(unsigned int mode, const VertexArray& va, const Shader& shader, unsigned int numIndices);

    /**
	 * \brief Clear the screen buffer with a given color
	 * \param color A glm::vec4 object specifies all four channels RGBA
	 */
	void Clear(const glm::vec4& color);

    /**
	 * \brief Enable OpenGL blending. Use adding and src_alpha for source and one_minus_src_alpha for destination
	 */
	void EnableBlending();

    /**
	 * \brief Disable OpenGL blending
	 */
	void DisableBlending();

    /**
	 * \brief Change PolygonMode to GL_LINE
	 */
	void EnableWireFrameMode();

    /**
	 * \brief Change PolygonMode to GL_FILL
	 */
	void DisableWireFrameMode();

    /**
	 * \brief Enable OpenGL depth testing
	 */
	void EnableDepthTest();

    /**
	 * \brief Disable OpenGl depth testing
	 */
	void DisableDepthTest();

}; // class Renderer