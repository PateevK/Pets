#pragma once
#include <glad/glad.h>
#include "shaderLoader.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../timer/timer.cpp"
 


class ShaderProgram {
	GLuint VS_ID, FS_ID, PR_ID;
	int success;
	char info[1024];
	const char* path;
public:
	ShaderProgram() = delete;
	ShaderProgram(const char* _path);
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetVec3(const char* name, glm::vec3 value) const;
	void SetMat4(const char* name, glm::mat4 value) const;
	void SetUnii(const char* name, int value) const;
	void ShaderLog(GLuint ID);
	void ProgramLog(GLuint ID);
	void Use() const;
	GLuint GetVS() const;
	GLuint GetFS() const;
	GLuint GetPR() const;
};
