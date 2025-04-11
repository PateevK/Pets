#pragma once

#include <string>
#include <string_view>
#include <vector>
#include "../shaderClass/shader.hpp"
#include "../model&mesh/Mesh.h"
#include "../textures/texture.hpp"
#include "../timer/timer.cpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
	Model() = delete;
	Model(const char* path) {
		PROFILE_FUNC()
		loadModel(path);
	}
	~Model();

	void Draw(ShaderProgram& Shader);
	std::vector<Mesh> getMeshes() {
		return meshes_m;
	}

private:
	std::vector<Mesh> meshes_m;
	std::vector<Texture> texturesLoaded;
	std::string directory;
	
	
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};