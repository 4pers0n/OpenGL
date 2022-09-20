#include "Renderer.h"

void Renderer::DrawArrays(const unsigned mode, const VertexBuffer& vb, const Shader& shader, const unsigned numTriangles)
{
	vb.Bind();
	shader.Bind();

	GLCall(glDrawArrays(mode, 0, numTriangles));
}

void Renderer::DrawElements(const unsigned mode, const VertexArray& va, const Shader& shader, const unsigned numIndices)
{
	va.Bind();
	shader.Bind();

	GLCall(glDrawElements(mode, numIndices, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear(const glm::vec4& color)
{
	GLCall(glClearColor(color.r, color.g, color.b, color.a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::EnableBlending()
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glBlendEquation(GL_FUNC_ADD));
}

void Renderer::DisableBlending()
{
	GLCall(glDisable(GL_BLEND));
}

void Renderer::EnableWireFrameMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::DisableWireFrameMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
