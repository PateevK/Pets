#include "shader.hpp"


ShaderProgram::ShaderProgram(const char* _path) : path(_path) {
		ShaderLoader data(path);
		PR_ID = glCreateProgram();
		VS_ID = glCreateShader(GL_VERTEX_SHADER);
		FS_ID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(VS_ID, 1, data.GetVertexShaderSource(), 0);
		glShaderSource(FS_ID, 1, data.GetFragmentShaderSource(), 0);
		glCompileShader(VS_ID);
		glCompileShader(FS_ID);
		glAttachShader(PR_ID, VS_ID);
		glAttachShader(PR_ID, FS_ID);
		glLinkProgram(PR_ID);
		ShaderLog(VS_ID);
		ShaderLog(FS_ID);
		ProgramLog(PR_ID);
		glDeleteShader(VS_ID);
		glDeleteShader(FS_ID);
		
	}

void ShaderProgram::SetInt(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(PR_ID, name), value);
}

void ShaderProgram::SetFloat(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(PR_ID, name), value);
}

void ShaderProgram::SetVec3(const char* name, glm::vec3 value) const {
	glUniform3fv(glGetUniformLocation(PR_ID, name), 1, glm::value_ptr(value));
}
	
void ShaderProgram::SetMat4(const char* name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(PR_ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

	void ShaderProgram::SetUnii(const char* name, int value) const{
		glUniform1i(glGetUniformLocation(PR_ID, name), value);
	}

	void ShaderProgram::ShaderLog(GLuint ID) {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, sizeof(info), 0, info);
			std::cout << " :: " << path << "\n" << info;
		}
	}

	void ShaderProgram::ProgramLog(GLuint ID) {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, sizeof(info), 0, info);
			std::cout << " :: " << path << "\n" << info;
		}
	}

	void ShaderProgram::Use() const {
		glUseProgram(PR_ID);
	}

	GLuint ShaderProgram::GetVS() const {
		return VS_ID;
	}
	GLuint ShaderProgram::GetFS() const {
		return FS_ID;
	}
	GLuint ShaderProgram::GetPR() const {
		return PR_ID;
	}