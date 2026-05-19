#include "stdafx.h"
#include "ImageLoader.hpp"

ImageLoader::ImageLoader()
{
}

void ImageLoader::init()
{
	m_imageTable[U"CommandWindow"] = Texture(U"./image/CommandWindow.png");
	m_imageTable[U"BattleBg"] = Texture(U"./image/ForestBg.jpg");
}
