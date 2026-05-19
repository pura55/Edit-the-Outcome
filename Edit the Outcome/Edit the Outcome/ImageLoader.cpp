#include "stdafx.h"
#include "ImageLoader.hpp"

ImageLoader::ImageLoader()
{
}

void ImageLoader::init()
{
	
}

void ImageLoader::LoadTitleAssets()
{
}

void ImageLoader::ClearTitleAssets()
{
}

void ImageLoader::LoadBattleAssets()
{
	TextureAsset::Register(U"CommandWindow", U"./image/CommandWindow.png");
	TextureAsset::Register(U"BattleBg", U"./image/ForestBg.jpg");
}

void ImageLoader::ClearBattleAssets()
{
	TextureAsset::UnregisterAll();
}
