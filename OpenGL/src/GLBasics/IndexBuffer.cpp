#include "IndexBuffer.h"

#include "../Utils/GLDebugHelper.h"

namespace GLBasics
{
    IndexBuffer::IndexBuffer(const unsigned* data, unsigned count)
        : m_RendererID(0), m_Count(count)
    {
        GLCall(glGenBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }

    IndexBuffer::~IndexBuffer()
    {
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void IndexBuffer::Bind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void IndexBuffer::UnBind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}  // namespace GLBasics
