#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// コマンドの状態を表す列挙体
/// </summary>
enum class CommandState
{
	Init,
	Idle,
	Active,
};

/// <summary>
/// コマンドタイプを表す列挙体
/// </summary>
enum class CommandType
{
	Init,
	Idle,
	Attack,
	Skills
};

/// <summary>
/// 前方宣言
/// </summary>
class BattleSystem;

/// <summary>
/// コマンドシステム
/// 
/// コマンドウィンドウを表示して、コマンド選択を管理するクラス
/// </summary>
class CommandSystem : public GameObject
{
/// <summary>
/// 基本的な関数
/// </summary>
public:
	CommandSystem();
	~CommandSystem();
	void Update()override;
	void Draw()override;

/// <summary>
/// Function関数
/// </summary>
private:
	void SelectCommand();
	void RecastTimer();

/// <summary>
/// Getter関数/Setter関数
/// </summary>
public:
	void SetReference();
	//コマンドの状態がIdleかどうかを返す関数
	bool GetIsStateIdle() const 
	{
		if(currentCommandState == CommandState::Idle)
		{ 
			return true;
		}
		else
		{ 
			return false;
		}
	}
	//コマンドの状態をActiveにする関数
	void SetStateActive() { currentCommandState = CommandState::Active; }
	//コマンドの指数を返す関数
	int GetCurrentCommandIndex() const { return currentCommandIndex; }
	//コマンドが決定されたかどうかを返す関数
	bool GetIsCommandDecide()const { return isCommandDecide; }
	//コマンドが確定されたかどうかを返す関数
	bool GetIsCommandConfirme() const { return isCommandConfirme; }

/// <summary>
/// 列挙型の変数
/// </summary>
private:
	CommandState currentCommandState;
	CommandType currentCommandType;

/// <summary>
/// メンバー変数
/// </summary>
private: 
	//現在選択されているコマンドのインデックス
	int currentCommandIndex; 
	//現在のリキャスト時間
	float currentRecastTime;
	//リキャスト時間が終了したかどうか
	bool isRecastEnd;         
	//コマンド選択のハンドル
	bool isCommandDecide;
	//コマンド確定のハンドル
	bool isCommandConfirme;
	//コマンドをリキャストするまでにかかる時間
	const float commandRecastTime = 0.2f;

/// <summary>
/// 参照
/// </summary>
private:
	//バトルシステムを参照
	BattleSystem* battleSystem;
};