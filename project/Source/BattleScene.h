#pragma once
#include "../Library/SceneBase.h"
#include "BattleSystem.h"
#include "CommandSystem.h"
#include "BattleUI.h"


/// <summary>
/// バトルシーン
/// 
/// バトル進行を管理するシーン
/// </summary>

class BattleScene : public SceneBase
{
/// <summary>
/// 基本的な関数
/// </summary>
public:
	BattleScene();
	~BattleScene();
	void Update() override;
	void Draw() override;

private:
	bool isBattleEnded;

/// <summary>
/// インスタンスを格納する変数
/// </summary>
private:
	BattleSystem* battleSystem;
	CommandSystem* commandSystem;
	BattleUI* battleUI;

};
