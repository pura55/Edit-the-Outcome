#pragma once
#include "../Library/SceneBase.h"
#include "BattleSystem.h"
#include <string>

/// <summary>
/// バトルシーン
/// 
/// バトル進行を管理するシーン
/// </summary>

class BattleScene : public SceneBase
{
public:
	BattleScene();
	~BattleScene();
	void Update() override;
	void Draw() override;

	//バトルが終了したかどうかを設定する関数

private:
	bool isBattleEnded;
	BattleSystem* battleSystem = FindGameObject<BattleSystem>();
};
