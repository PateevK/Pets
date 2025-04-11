#pragma once
#include<glad/glad.h>

class VertexBuffer {
	GLuint ID;
public:
	VertexBuffer() = delete;
	VertexBuffer(float* array, int size);

	GLuint GetID() const;
	void Bind() const;
	void Unbind() const;
};