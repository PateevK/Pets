#include"vertexArray.hpp"

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &ID);
		Bind();
	}
	void VertexArray::Bind() const {
		glBindVertexArray(ID);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}
