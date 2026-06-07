#pragma once
#include <Siv3D.hpp>
#include <stack>
#include <queue>

// 前方宣言
class Player;
class Enemy;

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
	/// public関数
	/// </summary>
public:
	BattleSystem();
	void update() ;
	void draw() const;

	/// @brief 参照を取得する関数
	void SetReference(Player* player);

	/// @brief コマンドインプットの終了状況を設定する関数
	void SetCommandInputEnd(bool inputEnd) { m_isCommandInputEnd = inputEnd; }

	/// @brief バトルが終了しているかを伝える関数
	bool GetBattleEnd() { return m_isBattleEnd; }

	/// @brief CommandIndexを取得する関数
	int32 GetCommandIndex(){ return m_currentCommandIndex; }

	/// @brief メニュースタックがスキルの状態か確認する関数
	bool GetIsSkillMenu()
	{
		if (m_menuStack.top() == MenuState::Skill)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/// @brief 現在のプレイヤーのHpを取得する関数
	int32 GetCurrentPlayerHp() { return m_playerHp; }

	/// @brief 現在のプレイヤーのHpを取得する関数
	int32 GetCurrentEnemyHp() { return m_enemyHp; }


	/// <summary>
	/// private関数
	/// </summary>
private:
	/// @brief ステート初期化関数
	void StateInit();

	/// @brief スタート関数
	bool StateStart();

	/// @brief コマンドインプット関数
	void StateCommandInput();

	/// @brief 敵の行動関数
	bool StateEnemyAction();

	/// @brief ターンエンド関数
	void StateTurnEnd();

	/// @brief バトル終了関数
	void StateBattleEnd();

	/// @brief コマンドの入力をする関数
	void SelectCommandIndex();

	

	/// <summary>
	/// 変数
	/// </summary>
private:

	/// 列挙体 ///
#pragma region Enum
	//バトルステート
	BattleState m_state{ BattleState::Init };

	//コマンドタイプ
	CommandType m_type{ CommandType::Attack };
#pragma endregion

	// 現在のバトルステートを表示するテキスト
	String m_currentStateText{ U"Init" };

	// メニュー内のコマンド数
	int32 m_maxCommandIndex{ 3 };
	int32 m_minCommandIndex{ 0 };
	// 現在選択されているコマンドのインデックス
	int32 m_currentCommandIndex{ m_minCommandIndex };

	int32 m_playerHp{ 1 };

	int32 m_enemyHp{ 1 };

	// プレイヤーの入力が終了したかどうかのフラグ
	bool m_isCommandInputEnd{ false };

	// 敵の行動が狩猟したかどうかのフラグ
	bool m_isEnemyActionEnd{ false };

	// バトルが終了したかどうかのフラグ
	bool m_isBattleEnd{ false };


	/// 構造体変数 ///
#pragma region StructureVariable
	//コマンドメニューのスタック
	std::stack<MenuState> m_menuStack;

	//バトルの状態のキュー
	std::queue<BattleState> m_battleQueue;
#pragma endregion


	/// ポインタの保持 ///
#pragma region Pointer
	// プレイヤーのポインタを保持
	Player* m_player{ nullptr };

	// エネミーのポインタを保持
	Enemy* m_enemy{ nullptr };
#pragma endregion

};

