#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

Texture TextureCache::GetTexture(std::string Path)
{
	std::map<std::string, Texture>::iterator mit = m_TextureMap.find(Path);

	if (mit == m_TextureMap.end()) {
		Texture texture = ImageLoader::LoadPNG(Path);

		m_TextureMap.insert(make_pair(Path, texture));

		return texture;
	}
	return mit->second;
}
