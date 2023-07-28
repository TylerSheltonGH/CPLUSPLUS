#include "ResourceManager.h"

TextureCache ResourceManager::m_TextureCache;

Texture ResourceManager::GetTexture(std::string Path)
{
	return m_TextureCache.GetTexture(Path);
}
