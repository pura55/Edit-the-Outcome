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
	/// 背景 ///
	TextureAsset::Register(U"BattleBg", U"./image/ForestBg.jpg");

	/// キャラクター ///
	TextureAsset::Register(U"Swordsman", U"./image/player/Swordsman/Swordsman_with_shadows/Swordsman.png");
	TextureAsset::Register(U"Slime", U"./image/enemy/Slime/Slime_with_shadows/Slime.png");
	TextureAsset::Register(U"Orc", U"./image/enemy/Orc/Orc_with_shadows/Orc.png");

	/// UI ///
	TextureAsset::Register(U"CommandWindow", U"./image/CommandWindowSmall.png");
	TextureAsset::Register(U"SubCommandWindow", U"./image/CommandWindow.png");
	TextureAsset::Register(U"EmptyHealthbar", U"./image/healthbar_empty.png");
	TextureAsset::Register(U"FullHealthbar", U"./image/healthbar_full.png");
	TextureAsset::Register(U"SelectArrow", U"./image/Arrows_pack.png");
}

void ImageLoader::ClearBattleAssets()
{
	TextureAsset::UnregisterAll();
}
