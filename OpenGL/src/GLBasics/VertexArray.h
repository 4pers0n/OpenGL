#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace GLBasics
{
    /**
     * \brief VertexArray class representing a VertexArray Object in OpenGL
     */
    class VertexArray
    {
    private:
        unsigned int m_RendererID;

    public:
        /**
         * \brief Constructs an empty VertexArray Object
         */
        VertexArray();

        /**
         * \brief Calls the underlying OpenGL functions to delete the VAO
         */
        ~VertexArray();

        /**
         * \brief Bind VertexBuffer and its layout to this VAO
         * \param vb A VertexBuffer class object
         * \param layout A VertexBufferLayout class object that corresponds to the vb
         */
        void BindBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;

        /**
         * \brief Bind Vertexbuffer, its layout, and its IndexBuffer to this VAO
         * \param vb A VertexBuffer class object
         * \param layout A VertexBufferLayout class object that corresponds to the vb passed in
         * \param ib A IndexBuffer class object that corresponds to the vb passed in
         */
        void BindBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const IndexBuffer& ib) const;

        /**
         * \brief Bind this VAO
         */
        void Bind() const;

        /**
         * \brief UnBind this VAO
         */
        void UnBind() const;

    };  // class VertexArray
}  // namespace GLBasics