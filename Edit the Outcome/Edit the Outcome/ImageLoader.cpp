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
	TextureAsset::Register(U"BattleBg", U"./image/Bg/ForestBg_1280x720.jpg");
	TextureAsset::Register(U"LootBgBar", U"./image/Bg/loot_bar.jpb");
	TextureAsset::Register(U"LootBgMagic", U"./image/Bg/loot_magic_b.jpg");

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
	TextureAsset::Register(U"DwarfKind", U"./image/dwarf_kind.png");
	TextureAsset::Register(U"LootFrame", U"./image/UI_wood_frame.png");
	TextureAsset::Register(U"SpeechFrame", U"./image/UI_wood_frameSpeech02.png");
}

void ImageLoader::ClearBattleAssets()
{
	TextureAsset::UnregisterAll();
}
