#pragma once
#include <Siv3D.hpp>
#include <stack>
#include <queue>

// 前方宣言
class CommandManager;
class EnemyActionManager;
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
	void update(CommandManager& commandMangager, EnemyActionManager& enemyActionManager) ;
	void draw() const;

	/// @brief 外部オブジェクトへの参照を設定する関数
	void SetReference(Player* player, std::vector<Enemy*> enemies);

	/// @brief バトルが終了しているかを伝える関数
	bool GetBattleEnd() { return m_isBattleEnd; }


	/// <summary>
	/// private関数
	/// </summary>
private:
	/// @brief ステート初期化関数
	void StateInit(CommandManager& commandManager);

	/// @brief スタート関数
	bool StateStart();

	/// @brief コマンドインプット関数
	void StateCommandInput(CommandManager& commandManager);

	/// @brief 敵の行動関数
	bool StateEnemyAction(EnemyActionManager& enemyActionManager);

	/// @brief ターンエンド関数
	void StateTurnEnd();

	/// @brief バトル終了関数
	void StateBattleEnd();

	/// <summary>
	/// 変数
	/// </summary>
private:

	/// 列挙体 ///
#pragma region Enum
	//バトルステート
	BattleState m_state{ BattleState::Init };
#pragma endregion

	// 敵の行動が狩猟したかどうかのフラグ
	bool m_isEnemyActionEnd{ false };

	// バトルが終了したかどうかのフラグ
	bool m_isBattleEnd{ false };

	// コマンドを選択したかどうかを表すフラグ
	bool m_isSelected{ false };

	bool m_isEnemyActed{ false };


	/// 構造体変数 ///
#pragma region StructureVariable
	//バトルの状態のキュー
	std::queue<BattleState> m_battleQueue;
#pragma endregion

	/// ポインタの保持 ///
#pragma region Pointer
	// プレイヤーのポインタを保持
	Player* m_player{ nullptr };

	// エネミーのポインタを保持
	std::vector<Enemy*> m_enemies{ nullptr };
#pragma endregion

};

