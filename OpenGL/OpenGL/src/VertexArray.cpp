#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray() {
	// vertex array 
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const {
	vb.Bind();
	Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (size_t i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		unsigned int index = static_cast<unsigned int>(i);
		// We call this function once because we only have one attribute(position)
		// para - index : the index of this attribute
		// para - size : how many types are inside this attribute
		// para - type : the type of element inside this attribute
		// para - normalized : boolean of if to normalize the data
		// para - stride : offset to go to the next vertex
		// para - pointer : specifies an offset of the first component
		//                  of the first generic vertex attribute in the array
		//                  (the offset to an attribute)
		GLCall(glVertexAttribPointer(index, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset));
		// used to enable the attribute above. Again state machine,
		// only need to specify the index. Can be called before the line above.
		GLCall(glEnableVertexAttribArray(index));

		offset += element.count * VertexBufferElement::GetTypeSize(element.type);
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const {
	GLCall(glBindVertexArray(0));
}
