#pragma once
#include "../Library/GameObject.h"
#include <string>

/// <summary>
/// バトルステート
/// 
/// バトルの状態を表す列挙型
///  </summary>
enum class BattleState
{
	Init,         // 初期化
	Start,        // バトル開始
	PlayerInput,  // プレイヤーの入力
	EnemyAction,  // 敵の行動
	TurnEnd,      // ターン終了
	BattleEnd,    // バトル終了
};

/// <summary>
/// バトルシステム
/// 
/// バトルシステムを管理するクラス
/// </summary>
class BattleSystem : public GameObject
{
/// <summary>
/// バトルの状態に応じた処理を行う関数
/// </summary>
public:
	BattleSystem();
	~BattleSystem();
	void Update() override;
	void Draw() override;
	bool GetBattleEnd() { return isBattleEnd; }

/// <summary>
/// バトルの状態に応じた処理を行う関数
/// </summary>
private:
	void Init();
	bool Start();
	bool PlayerInput();
	bool EnemyAction();
	void TurnEnd();
	void BattleEnd();

private:
	BattleState state; //バトルステート
	std::string currentStateText;
	bool isBattleEnd;

};
