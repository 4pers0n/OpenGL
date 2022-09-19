#pragma once

namespace GLBasics
{
    /**
     * \brief IndexBuffer class representing one single IBO in OpenGL
     */
    class IndexBuffer
    {
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;

    public:
        /**
         * \brief Constructs a IBO. Client is responsible for freeing the data
         * \param data A const unsigned int pointer pointing to the beginning of the buffer
         * \param count The number of unsigned int inside the buffer
         */
        IndexBuffer(const unsigned int* data, unsigned int count);

        /**
         * \brief Calls the underlying OpenGL functions to delete the buffer
         */
        ~IndexBuffer();

        /**
         * \brief Bind the buffer stored in this IBO
         */
        void Bind() const;

        /**
         * \brief UnBind the buffer stored in this VBO
         */
        void UnBind() const;

        /**
         * \brief Get the number of indices stored inside this IBO
         * \return The number of indices
         */
        inline unsigned int GetCount() const { return m_Count; }

    };  // class IndexBuffer
}  // namespace GLBasics
