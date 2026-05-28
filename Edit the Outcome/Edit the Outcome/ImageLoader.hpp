#pragma once
#include <Siv3D.hpp>

class ImageLoader
{
public:
	ImageLoader();
	void init();
	//タイトルのイメージをロードする関数
	void LoadTitleAssets();
	//タイトルのイメージをクリアする関数
	void ClearTitleAssets();
	//バトル時のイメージをロードする関数
	void LoadBattleAssets();
	//バトル時のイメージをクリアする関数
	void ClearBattleAssets();
};


