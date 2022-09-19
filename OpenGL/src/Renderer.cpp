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
