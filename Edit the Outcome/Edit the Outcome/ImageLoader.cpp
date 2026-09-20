#include "stdafx.h"
#include "ImageLoader.hpp"

ImageLoader::ImageLoader()
{
}

void ImageLoader::init()
{
	
}

void ImageLoader::LoadAssets()
{
	/// 背景 ///
	TextureAsset::Register(U"BattleBg", U"./image/Bg/ForestBg_1280x720.jpg");

	/// キャラクター ///
	TextureAsset::Register(U"Swordsman", U"./image/player/Swordsman/Swordsman.png");
	TextureAsset::Register(U"Slime", U"./image/enemy/Slime/Slime.png");
	TextureAsset::Register(U"Orc", U"./image/enemy/Orc/Orc.png");
	TextureAsset::Register(U"Bat",U"./image/enemy/Bat/Bat.png");
	TextureAsset::Register(U"Skeleton", U"./image/enemy/Skeleton/Skeleton.png");
	TextureAsset::Register(U"Werewolf", U"./image/enemy/Werewolf/Werewolf.png");

	/// UI ///
	TextureAsset::Register(U"CommandWindow", U"./image/CommandWindowSmall.png");
	TextureAsset::Register(U"SubCommandWindow", U"./image/CommandWindow.png");
	TextureAsset::Register(U"EmptyHealthbar", U"./image/healthbar_empty.png");
	TextureAsset::Register(U"FullHealthbar", U"./image/healthbar_full.png");
	TextureAsset::Register(U"SelectArrow", U"./image/Arrows_pack.png");
	TextureAsset::Register(U"Explanation1", U"./image/explanation/explanation_1.png");
	TextureAsset::Register(U"Explanation2", U"./image/explanation/explanation_2.png");
	TextureAsset::Register(U"Explanation3", U"./image/explanation/explanation_3.png");
	TextureAsset::Register(U"Explanation4", U"./image/explanation/explanation_4.png");
}

void ImageLoader::ClearBattleAssets()
{
	TextureAsset::UnregisterAll();
}
