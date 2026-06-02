#pragma once
#include <Siv3D.hpp>

class ImageLoader
{
public:
	ImageLoader();
	void init();

	/// @brief タイトルの画像をロードする関数
	void LoadTitleAssets();

	/// @brief タイトルの画像をクリアする関数
	void ClearTitleAssets();

	/// @brief バトル時の画像をロードする関数
	void LoadBattleAssets();

	/// @brief バトル時の画像をクリアする関数
	void ClearBattleAssets();

};


