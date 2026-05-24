#pragma once
#include <Siv3D.hpp>
#include <stack>
#include <queue>

/// <summary>
/// バトルステート
/// 
/// バトルの状態を表す列挙型
///  </summary>
enum class BattleState
{
	Init,         // 初期化
	Start,        // バトル開始
	CommandInput, // プレイヤーの入力
	EnemyAction,  // 敵の行動
	TurnEnd,      // ターン終了
	BattleEnd,    // バトル終了
};

/// <summary>
/// コマンドステート
/// 
/// コマンドの状態を表す列挙型
///  </summary>
enum class MenuState
{
	Base,
	Skill
};

/// <summary>
/// コマンドタイプ
///  </summary>
enum class CommandType
{
	Attack,
	Diffence,
	Skills
};

/// <summary>
/// バトルシステム
/// 
/// バトルシステムを管理するクラス
/// </summary>
class BattleSystem  
{
	/// <summary>
	/// 基本的な関数
	/// </summary>
public:
	BattleSystem();
	void update() ;
	void draw() const;

	/// <summary>
	/// Getter/Setter関数
	/// </summary>
public:
	/*void SetReference();*/ //使用するかもしれないので仮コメント
	void SetPlayerInputEnd(bool inputEnd) { isCommandInputEnd = inputEnd; }
	bool GetBattleEnd() { return isBattleEnd; }

	/// <summary>
	/// バトルの状態に応じた処理を行う関数
	/// </summary>
private:
	//ステート初期化関数
	void StateInit();
	//スタート関数
	bool StateStart();
	//コマンドインプット関数
	void StateCommandInput();
	//敵の行動関数
	bool StateEnemyAction();
	//ターンエンド関数
	void StateTurnEnd();
	//バトル終了関数
	void StateBattleEnd();

	/// <summary>
	/// 機能関数
	/// </summary>
private:
	void SelectCommandIndex();

	/// <summary>
	/// 一般型名変数
	/// </summary>
private:
	//バトルステート
	BattleState state = { BattleState::Init };

	//コマンドタイプ
	CommandType type = { CommandType::Attack };

	//現在のバトルステートを表示するテキスト
	String currentStateText = { U"Init" };

	//メニュー内のコマンド数
	int MaxCommandIndex = { 3 };
	//現在選択されているコマンドのインデックス
	int currentCommandIndex = { 0 };


	//プレイヤーの入力が終了したかどうかのフラグ
	bool isCommandInputEnd = { false };
	//敵の行動が狩猟したかどうかのフラグ
	bool isEnemyActionEnd = { false };
	//バトルが終了したかどうかのフラグ
	bool isBattleEnd = { false };

	/// <summary>
	/// 構造体変数
	/// </summary>
private:
	//コマンドメニューのスタック
	std::stack<MenuState> menuStack;

	//バトルの状態のキュー
	std::queue<BattleState> battleQueue;

};

