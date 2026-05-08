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
/// 前方宣言
/// </summary>
class CommandSystem;

/// <summary>
/// バトルシステム
/// 
/// バトルシステムを管理するクラス
/// </summary>
class BattleSystem : public GameObject
{

/// <summary>
/// 基本的な関数
/// </summary>
public:
	BattleSystem();
	~BattleSystem();
	void Update() override;
	void Draw() override;

/// <summary>
/// Getter/Setter関数
/// </summary>
public:
	void SetReference();
	void SetPlayerInputEnd(bool inputEnd) { isPlayerInputEnd = inputEnd; }
	bool GetBattleEnd() { return isBattleEnd; }


private:
	/// バトルの状態に応じた処理を行う関数
	void StateInit();
	bool StateStart();
	void StatePlayerInput();
	bool StateEnemyAction();
	void StateTurnEnd();
	void StateBattleEnd();

/// <summary>
/// 列挙体の変数
/// </summary>
private:
	BattleState state; //バトルステート

/// <summary>
/// メンバー変数
/// </summary>
private:
	//現在のバトルステートを表示するテキスト
	std::string currentStateText;
	//プレイヤーの入力が終了したかどうかのフラグ
	bool isPlayerInputEnd;
	//敵の行動が狩猟したかどうかのフラグ
	bool isEnemyActionEnd;
	//バトルが終了したかどうかのフラグ
	bool isBattleEnd;

/// <summary>
///参照
/// </summary>
private:
	//コマンドシステムを参照
	CommandSystem* commandSystem;
};
