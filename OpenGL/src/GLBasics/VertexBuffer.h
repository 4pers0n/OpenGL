#pragma once

namespace GLBasics
{
    /**
     * \brief VertexBuffer class representing one single VBO in OpenGL
     */
    class VertexBuffer
    {
    private:
        unsigned int m_RendererID;

    public:

        /**
         * \brief Constructs a VBO. Client is responsible for freeing the data
         * \param data A const void pointer pointing to the beginning of the buffer
         * \param size The total bytes of the buffer
         */
        VertexBuffer(const void* data, unsigned int size);

        /**
         * \brief Calls the underlying OpenGL functions to delete the buffer
         */
        ~VertexBuffer();

        /**
         * \brief Bind the buffer stored in this VBO
         */
        void Bind() const;

        /**
         * \brief UnBind the buffer stored in this VBO
         */
        void UnBind() const;

    };  // class VertexBuffer
}  // namespace GLBasics
