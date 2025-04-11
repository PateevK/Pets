#include"vertexBuffer.hpp"




VertexBuffer::VertexBuffer(float* array, int size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, array, GL_STATIC_DRAW);
}

GLuint VertexBuffer::GetID() const {
	return ID;
}

void VertexBuffer::Bind() const{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}