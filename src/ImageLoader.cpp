#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include "ImageLoader.h"
#include "IOManager.h"
#include "stb_image.h"

#include "Log.h"

Texture ImageLoader::LoadPNG(std::string Path)
{
	Texture texture = {}; //set everything to 0

	int width, height, channels;

	//stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(Path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (image == nullptr) {
		VOID_CORE_ERROR("Failed to load image.");
	}

	glGenTextures(1, &(texture.id));

	glBindTexture(GL_TEXTURE_2D, texture.id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);

	texture.width = width;
	texture.height = height;

	return texture;
}
