#include"texture.hpp"

TextureLoader::TextureLoader(const char* path) {
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		LoadTex(path);
		GLenum format = 0;
		if (imageData.ch == 1)
			format = GL_RED;
		else if (imageData.ch == 3)
			format = GL_RGB;
		else if (imageData.ch == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, imageData.x, imageData.y, 0, format, GL_UNSIGNED_BYTE, imageData.texImage);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData.texImage);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

TextureLoader::~TextureLoader() {
		//glDeleteTextures(1, &ID);
	}

	GLuint TextureLoader::GetID() const {
		return ID;
	}

	int TextureLoader::GetUnit() const {
		return m_texUnit;
	}

	void TextureLoader::Bind(int texUnit) {
		m_texUnit = texUnit;
		glActiveTexture(GL_TEXTURE0 + texUnit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	uchar* TextureLoader::LoadTex(const char* path) {
		imageData.texImage = stbi_load(path, &imageData.x, &imageData.y, &imageData.ch, 0);
		if (!imageData.texImage) std::cout << "TextureLoader-Error::" << path << "\n";
		return imageData.texImage;
	}