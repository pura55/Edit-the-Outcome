#pragma once
#include "../Library/GameObject.h"
#include "ImageLoader.h"

/// <summary>
/// コモン
/// 
/// 複数のシーンで共通して使うものをまとめるクラス
/// </summary>
class Common : public GameObject
{
public:
	Common();
	~Common();
	void Update() override;

private:
	ImageLoader* imageLoader;
};
