#pragma once

#include "../Utils/GLDebugHelper.h"

namespace GLBasics
{
    /**
     * \brief VertexBuffer class representing one single VBO in OpenGL
     */
    class VertexBuffer
    {
    private:
        unsigned int m_RendererID;  // object identifier
    public:

        /**
         * \brief Constructs a VBO. Client is responsible for freeing the data
         * \param data a const void pointer pointing to the beginning of the buffer
         * \param size the total bytes of the buffer
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
    };
}
