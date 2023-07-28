#pragma once
#include "TextureCache.h"

class ResourceManager
{
public:
	static Texture GetTexture(std::string Path);

private:
	static TextureCache m_TextureCache;
};

