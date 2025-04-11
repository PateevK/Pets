#pragma once
#include<glad/glad.h>

class VertexArray {
	GLuint ID;
public:
	VertexArray();

	void Bind() const;
	void Unbind() const;
};
