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
	TextureAsset::Register(U"BattleBg", Resource(U"image/Bg/ForestBg_1280x720.jpg"));

	/// キャラクター ///
	TextureAsset::Register(U"Swordsman", Resource(U"image/player/Swordsman/Swordsman.png"));
	TextureAsset::Register(U"Slime", Resource(U"image/enemy/Slime/Slime.png"));
	TextureAsset::Register(U"Orc", Resource(U"image/enemy/Orc/Orc.png"));
	TextureAsset::Register(U"Bat", Resource(U"image/enemy/Bat/Bat.png"));
	TextureAsset::Register(U"Skeleton", Resource(U"image/enemy/Skeleton/Skeleton.png"));
	TextureAsset::Register(U"Werewolf", Resource(U"image/enemy/Werewolf/Werewolf.png"));

	/// UI ///
	TextureAsset::Register(U"CommandWindow", Resource(U"image/CommandWindowSmall.png"));
	TextureAsset::Register(U"SubCommandWindow", Resource(U"image/CommandWindow.png"));
	TextureAsset::Register(U"EmptyHealthbar", Resource(U"image/healthbar_empty.png"));
	TextureAsset::Register(U"FullHealthbar", Resource(U"/image/healthbar_full.png"));
	TextureAsset::Register(U"SelectArrow", Resource(U"/image/Arrows_pack.png"));
	TextureAsset::Register(U"Explanation1", Resource(U"/image/explanation/explanation_1.png"));
	TextureAsset::Register(U"Explanation2", Resource(U"/image/explanation/explanation_2.png"));
	TextureAsset::Register(U"Explanation3", Resource(U"/image/explanation/explanation_3.png"));
	TextureAsset::Register(U"Explanation4", Resource(U"/image/explanation/explanation_4.png"));
}

void ImageLoader::ClearBattleAssets()
{
	TextureAsset::UnregisterAll();
}
