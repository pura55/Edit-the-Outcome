#pragma once
#include "../Library/GameObject.h"
#include <cassert>

/// <summary>
/// イメージローダー
/// 
/// 画像を読み込んで、他のクラスに提供するクラス
/// </summary>
class ImageLoader : public GameObject
{
public:
	ImageLoader();
	~ImageLoader();
	void Update() override;

/// <summary>
/// Getter関数
/// </summary>
public:
	int GetCommandWindow() const{ return commandWindow; }

/// <summary>
/// 読み込んだ画像を格納する変数
/// </summary>
private:
	int commandWindow;
};