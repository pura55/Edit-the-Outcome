#pragma once
#include <Siv3D.hpp>

class ImageLoader
{
public:
	ImageLoader();
	void init();
	void LoadTitleAssets();
	void ClearTitleAssets();
	void LoadBattleAssets();
	void ClearBattleAssets();
};


