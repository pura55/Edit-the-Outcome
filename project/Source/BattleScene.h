#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// 前方宣言
/// </summary>
class BattleSystem;
class CommandSystem;
class BattleUI;

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
/// 参照
/// </summary>
private:
	//バトルシステムを参照
	BattleSystem* battleSystem;
	//コマンドシステムを参照
	CommandSystem* commandSystem;
	//バトルUIを参照
	BattleUI* battleUI;

};
