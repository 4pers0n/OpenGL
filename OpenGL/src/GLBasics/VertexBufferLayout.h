#pragma once

#include <vector>

#include "../Utils/GLDebugHelper.h"

namespace GLBasics
{

    /**
     * \brief Represent a single property inside of a single vertex
     */
    struct VertexBufferElement
    {
	    unsigned int type;
	    unsigned int count;
	    unsigned int normalized;  // (boolean but int for memory alignment)

        /**
	     * \brief Get the type size from a GL type
	     * \param type An OpenGL type that is one of GL_FLOAT, GL_UNSIGNED_INT, and GL_UNSIGNED_BYTE 
	     * \return An unsigned integer that is the size of the OpenGL type 
	     */
	    static unsigned int GetTypeSize(unsigned int type)
        {
		    switch (type)
	        {
		        case GL_FLOAT:			return sizeof(GLfloat);
		        case GL_UNSIGNED_INT:	return sizeof(GLuint);
		        case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
                default:                ASSERT(false);  // other types are unsupported;
            }
		    return 0;
	    }
    };  // struct VertexBufferElement

    /**
	 * \brief Represent the whole layout for all the properties that a single vertex has
	 */
	class VertexBufferLayout
    {
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;

	public:
		VertexBufferLayout()
			:m_Stride(0) {}

		~VertexBufferLayout() {}

		template<typename T>
		void Push(unsigned int count)
	    {
			ASSERT(false);  // other types unsupported
		}

        /**
		 * \brief Add a new property to a layout with the type float
		 * \param count The number of floats
		 */
		template<>
		void Push<float>(unsigned int count)
	    {
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
		}

		/**
		 * \brief Add a new property to a layout with the type unsigned int
		 * \param count The number of unsigned ints
		 */
		template<>
		void Push<unsigned int>(unsigned int count)
	    {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
		}

		/**
		 * \brief Add a new property to a layout with the type char
		 * \param count The number of chars
		 */
		template<>
		void Push<unsigned char>(unsigned int count)
	    {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
		}

        /**
		 * \brief Get the stride of all the properties added
		 * \return An unsigned int representing the stride
		 */
		inline unsigned int GetStride() const { return m_Stride; }

        /**
		 * \brief Get all the properties added in this layout if needed
		 * \return A vector of all the elements stored as VertexBufferElement
		 */
		inline std::vector<VertexBufferElement> GetElements() const
	    {
			return m_Elements;
		}
	};  // class VertexBufferLayout
}  // namespace GLBasics