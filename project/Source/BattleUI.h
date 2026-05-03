#pragma once
#include "../Library/GameObject.h"
#include "ImageLoader.h"

/// <summary>
/// バトルUI
/// 
/// バトルでコマンド振動やHPバーなどのUIを表示するクラス
/// </summary>
class BattleUI : public GameObject
{
/// <summary>
/// 基本的な関数
/// </summary>
public:
	BattleUI();
	~BattleUI();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 画像を格納する変数
	/// </summary>
private:
	ImageLoader* imageLoader = FindGameObject<ImageLoader>();
};