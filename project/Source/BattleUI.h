#pragma once
#include "../Library/GameObject.h"
#include "ImageLoader.h"
#include "CommandSystem.h"

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
/// メンバー変数
/// </summary>
private:
	//コマンドインデックス
	int currentCommandIndex;
	//コマンドウィンドウの座標
	const VECTOR2 commandWindowPos = { 64 * 5, 64 * 11 };
	//矢印の三点の座標
	const VECTOR2 Triangle_FirstPos = { commandWindowPos.x + 32 * 1, commandWindowPos.y + 32 };
	const VECTOR2 Triangle_SecondPos = { commandWindowPos.x + 32 * 1, commandWindowPos.y + 32 + 16 };
	const VECTOR2 Triangle_ThirdPos = { commandWindowPos.x + 32 * 1 + 16, commandWindowPos.y  + 32 + 8};

	/// <summary>
	/// インスタンスを格納する変数
	/// </summary>
private:
	ImageLoader* imageLoader;
	CommandSystem* commandSystem;
};