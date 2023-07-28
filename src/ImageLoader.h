#pragma once
#include "Texture.h"
#include <string>

class ImageLoader
{
public:
	static Texture LoadPNG(std::string Path);
};

