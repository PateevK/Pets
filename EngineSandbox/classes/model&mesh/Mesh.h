#pragma once
#include <vector>
#include <string>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "../shaderClass/shader.hpp"


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh{

	void setupMesh();

	GLuint VAO, VBO, EBO;

public:
	Mesh() = delete;
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, 
		std::vector<Texture> textures);

	void Draw(ShaderProgram& shader);

	std::vector<Vertex> vertices_m;
	std::vector<GLuint> indices_m;
	std::vector<Texture> textures_m;
};