#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    // create a buffer, m_RendererID is the output parameter
    GLCall(glGenBuffers(1, &m_RendererID));
    // bind the buffer to an array buffer inside vram
    // enter the state of having this buffer (no need to specify the buffer later)
    // (imagine seleting a layer in Photoshop)
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    // specify the data(we can specify the size first)
    // check the docs.GL for this function
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
