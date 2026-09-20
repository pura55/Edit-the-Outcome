#pragma once
#include <Siv3D.hpp>
#include "StatusUI.hpp"
#include "CommandWindow.hpp"
#include "SelectArrow.hpp"
#include "DamageDisplay.hpp"
#include "Result.hpp"

// 前方宣言
class BattleSystem;
class CommandManager;
class TargetSelectSystem;
class Player;
class Enemy;

/// <summary>
/// バトルUI
/// 
/// バトルでコマンド振動やHPバーなどのUIを表示するクラス
/// </summary>
class BattleUI
{
	/// <summary>
	/// 基本的な関数
	/// </summary>
public:
	BattleUI();
	void update();
	void draw() const;

	/// <summary>
	/// Setter/Getter
	/// </summary>
public:
	/// @brief 外部オブジェクトへの参照を設定する関数
	void SetReference(BattleSystem& battleSystem, CommandManager& commandManager ,TargetSelectSystem& targetSelectSystem, Player& player, std::vector<std::unique_ptr<Enemy>>& enemy);

	/// @brief ダメージ表示する関数
	void ShowDamage(int32 damage, Vec2 position);

	/// @brief ダメージ表示する関数
	/// @param skillNum スキルの回数
	void ShowDamage(int32 damage, Vec2 position, int32 skillNums);

	void SetWin() { m_isWin = true; }

	void SetLose() { m_isLose = true; }

private:
	/// @brief ダメージ表示をインキューする関数
	void DamageInQueue();

	/// @brief ダメージ表示を更新する関数
	void UpdateDamageDisplays();

	/// @brief ダメージ表示をキューに戻す関数
	void ReturnDamageQueue();

private:

	// ダメージ表示を保持する数
	int32 m_damageDisplayNumbers{ 10 };

	// 勝利フラグ
	bool m_isWin{ false };

	// 敗北フラグ
	bool m_isLose{ false };

	/// ポインタの保持 ///

#pragma region Pointer
	BattleSystem* m_battleSystem{ nullptr }; //バトルシステムのポインタを保持

	CommandManager* m_commandManager{ nullptr }; // コマンドマネージャーのポインタを保持

	TargetSelectSystem* m_targetSelectSystem{ nullptr }; //ターゲットセレクトシステムシステムのポインタを保持

	Player* m_player; // プレイヤーの参照

	std::vector<std::unique_ptr<Enemy>>* m_enemies; // 敵の参照
#pragma endregion

	/// UIの保持 ///
#pragma region UI
	StatusUI m_statusUI; // ステータスUI
	CommandWindow m_commandWindow; // コマンドウィンドウ
	SelectArrow m_selectArrow; // セレクトアロー
	Result m_result; // 結果

	std::queue<DamageDisplay*> m_damageDisplayQueue;
	std::vector<std::unique_ptr<DamageDisplay>> m_damageDisplay;
#pragma endregion

};
