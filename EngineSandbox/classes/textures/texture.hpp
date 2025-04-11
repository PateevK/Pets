#pragma once
#include <glad/glad.h>
#include<iostream>
#ifndef STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#endif
#define uchar unsigned char
class TextureLoader {
	struct ImageData {
		int x, y, ch;
		uchar* texImage;
	}imageData;
	GLuint ID;
	int m_texUnit;
public:
	TextureLoader() = delete;
	TextureLoader(const char* path);
	~TextureLoader();

	GLuint GetID() const;
	int GetUnit() const;
	void Bind(int texUnit);
	uchar* LoadTex(const char* path);
};