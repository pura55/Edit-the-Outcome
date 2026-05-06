#pragma once
#include "../Library/GameObject.h"
#include "ImageLoader.h"

/// <summary>
/// コマンドの状態を表す列挙体
/// </summary>
enum class Command
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
/// Fanction関数
/// </summary>
private:
	void SelectCommand();
	void RecastTimer();

	/// <summary>
	/// Getter関数
	/// </summary>
public:
	int GetCurrentCommandIndex() const { return currentCommandIndex; }
	int GetIsCommandDecide()const { return isCommandDecide; }

/// <summary>
/// 列挙型の変数
/// </summary>
private:
	Command currentCommand;
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
	////コマンド選択のハンドル
	bool isCommandDecide;
	//コマンドをリキャストするまでにかかる時間
	const float commandRecastTime = 0.2f;

/// <summary>
/// インスタンスを格納する変数
/// </summary>
private:
	ImageLoader* imageLoader;
};