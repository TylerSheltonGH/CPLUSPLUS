#pragma once
#include "Texture.h"
#include <map>
#include <string>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	Texture GetTexture(std::string Path);

private:
	std::map<std::string, Texture> m_TextureMap;
};

