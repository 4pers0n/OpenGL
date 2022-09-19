#include "VertexArray.h"

#include "../Utils/GLDebugHelper.h"

namespace GLBasics
{
    VertexArray::VertexArray()
        : m_RendererID(0)
    {
        GLCall(glGenVertexArrays(1, &m_RendererID));
        GLCall(glBindVertexArray(m_RendererID));
    }

    VertexArray::~VertexArray()
    {
        GLCall(glDeleteVertexArrays(1, &m_RendererID));
    }

    void VertexArray::BindBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
    {
        Bind();  // current VAO will automatically include all subsequent VBO bind
        vb.Bind();

        const auto& elements = layout.GetElements();
        unsigned int offset = 0;
        for (int index = 0; index < elements.size(); index++)
        {
            const auto& element = elements[index];

            GLCall(glVertexAttribPointer(index, element.count, element.type, element.normalized,
                layout.GetStride(), (const void*)offset));
            GLCall(glEnableVertexAttribArray(index));

            offset += element.count * VertexBufferElement::GetTypeSize(element.type);
        }
    }

    void VertexArray::BindBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const IndexBuffer& ib) const
    {
        Bind();  // current VAO will automatically include all subsequent VBO and IBO bind
        vb.Bind();
        ib.Bind();

        const auto& elements = layout.GetElements();
        unsigned int offset = 0;
        for (int index = 0; index < elements.size(); index++)
        {
            const auto& element = elements[index];

            GLCall(glVertexAttribPointer(index, element.count, element.type, element.normalized,
                layout.GetStride(), (const void*)offset));
            GLCall(glEnableVertexAttribArray(index));

            offset += element.count * VertexBufferElement::GetTypeSize(element.type);
        }
    }

    void VertexArray::Bind() const
    {
        GLCall(glBindVertexArray(m_RendererID));
    }

    void VertexArray::UnBind() const
    {
        GLCall(glBindVertexArray(0));
    }
}  // namespace GLBasics