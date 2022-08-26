#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count) {
    // index buffer object
    // has to be unsigned!!!
    //
    // create a buffer, m_RendererID is the output parameter
    GLCall(glGenBuffers(1, &m_RendererID));
    // bind the buffer to an array buffer inside vram
    // enter the state of having this buffer (no need to specify the buffer later)
    // (imagine seleting a layer in Photoshop)
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    // specify the data(we can specify the size first)
    // check the docs.GL for this function
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
