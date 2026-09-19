#pragma once
#include <Siv3D.hpp>

class ImageLoader
{
public:
	ImageLoader();
	void init();

	/// @brief バトル時の画像をロードする関数
	void LoadAssets();

	/// @brief バトル時の画像をクリアする関数
	void ClearBattleAssets();

};


