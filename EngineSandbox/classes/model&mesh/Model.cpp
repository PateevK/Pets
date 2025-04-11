#include "model.h"
void Model::loadModel(std::string path) {
    PROFILE_FUNC()
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
    std::cout << "Model loaded::" << directory << '\n';
}

Model::~Model() {
    for (int i = 0; i < meshes_m.size(); i++) {
        std::vector<Texture> textures_d = meshes_m[i].textures_m;
        for (int j = 0; j < textures_d.size(); j++) {
            glDeleteTextures(1, &textures_d[j].id);
            std::cout << "Texture deleted::" << textures_d[j].path << '\n';
        }
    }
};


void Model::processNode(aiNode* node, const aiScene* scene) {
    PROFILE_FUNC()
    for (int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_m.push_back(processMesh(mesh, scene));
    }
    for (int i = 0; i < node->mNumChildren;i++) {
        processNode(node->mChildren[i], scene);
        std::cout << "Nodes processed::" << i + 1 << " / " << node->mNumChildren << '\n';
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    PROFILE_FUNC()
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;
    {
        PROFILE_SCOPE("VERTICES")
            for (int i = 0; i < mesh->mNumVertices; i++) {
                //----------------------------VERTICES
                Vertex vertex;
                vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
                vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
                if (mesh->mTextureCoords[0])
                    vertex.texCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
                else
                    vertex.texCoords = { 0.0, 0.0 };

                vertices.push_back(vertex);
            }
    }
    //----------------------------INDICES
    {
        PROFILE_SCOPE("INDICES")
        for (int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
    }
    //----------------------------TEXTURES
    {
        PROFILE_SCOPE("TEXTURES")
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
                aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = loadMaterialTextures(material,
                aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }
    }
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
    std::string typeName) {
    PROFILE_FUNC()

    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string relativePath = directory + '/' + std::string(str.C_Str());
        bool skip = false;
        for (int j = 0; j < texturesLoaded.size(); j++) {
            if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            TextureLoader TextureData(relativePath.c_str());
            texture.id = TextureData.GetID();
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

void Model::Draw(ShaderProgram& Shader) {
    for (int i = 0; i < meshes_m.size(); i++) {
        meshes_m[i].Draw(Shader);
    }
}

