#pragma once
#include "CommandData.hpp"

class TargetSelectSystem;
class HealthManager;
class Player;
class Enemy;

/// <summary>
/// メニューステイト
/// 
/// ウィンドウメニューの状態を表す列挙型
///  </summary>
enum class MenuState
{
	Default,     // デフォルトで何も表示しない
	Base,        // ベースメニュー
	Skill,       // スキルメニュー
	SelectEnemy  // 敵選択画面
};

/// <summary>
/// ベースコマンドタイプ
///  </summary>
enum class BaseCommandType
{
	Attack,    // 攻撃
	Diffence,  // 守備
	Skills     // スキル
};

/// <summary>
/// コマンドマネージャー
///  </summary>
class CommandManager
{
public:
	CommandManager();
	void update();

	/// @brief コマンドデータの参照を設定する関数
	void SetData(std::vector<CommandData>& commandData);

	/// @brief 参照を登録する関数
	void SetReference(TargetSelectSystem& targetSelectSystem, HealthManager& healthManager, Player* player, std::vector<Enemy*> enemies);

	/// @brief エネミーの数を登録する関数
	void RegistMaxEnemiesNum() { m_maxEnemiesNum = m_enemies.size(); }

    /// @brief コマンドデータ内のコマンド名を配列として登録する関数
	void RegistCommandName();

	/// @brief 変数をリセットする関数
	void ResetVariable();

	/// @brief コマンド処理を更新する関数
	void UpdateCommandProcess(bool& isCommandSelected);

	/// @brief ベースメニューのコマンドを選択する関数
	void SelectBaseCommand(bool& isCommandSelected);

	/// @brief スキルメニューのコマンドを選択する関数 
	void SelectSkillCommand(bool& isCommandSelected);

	/// @brief コマンドの決定処理を管理する関数
	void ManageDecisionProcessing(bool& isCommandSelected);

	/// @brief コマンドウィンドウを見せれる状態かどうかを返す関数
	/// @return true:可能 false:不可能
	bool CanShowWindow()
	{
		if (m_menuStack.top() == MenuState::Default)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool GetIsSkillWindow()
	{
		if (m_menuStack.top() == MenuState::Skill)
		{
			return true;
		}
		else if (m_menuStack.top() == MenuState::SelectEnemy && m_baseCommandType == BaseCommandType::Skills)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/// @brief CommandIndexを取得する関数
	int32 GetCommandIndex() { return m_currentCommandIndex; }

	/// @brief targetSelectIndexを取得する関数
	int32 GetSelectIndex() { return m_targetSelectIndex; }

	bool GetIsShowArrow() { return m_isShowArrow; }

	/// @brief コマンドの名前を返す関数
	std::vector<String> GetCommandName() { return m_commandName; }

private:

	/// 列挙体 ///
	BaseCommandType m_baseCommandType{ BaseCommandType::Attack };



	/// 一般変数 ///

	const int32 m_baseMaxIndex{ 2 }; // ベースメニューのコマンドの最大値
	
	int32 m_currentCommandIndex{ 0 }; // 現在選択されているコマンドのインデックス

	int32 m_targetSelectIndex{ 0 };  // 選択しているターゲットのインデックス

	bool m_isTargetSelected{ false };  // ターゲットの選択がされているかどうかのフラグ

	int32 m_maxEnemiesNum{0}; // エネミーの最大数

	bool m_isShowArrow{ false };

	/// 構造体 ///
	std::stack<MenuState> m_menuStack; //コマンドウィンドウのスタック

	std::vector<String> m_commandName; // コマンドの名前


	/// 参照 ///
	std::vector<CommandData> m_commandData; // コマンドデータの参照

	TargetSelectSystem* m_targetSelectSystem{ nullptr }; // ターゲットセレクトシステムの参照

	HealthManager* m_healthManager{ nullptr }; // ヘルスマネージャーの参照

	Player* m_player{ nullptr };              // プレイヤーの参照

	std::vector<Enemy*> m_enemies{ nullptr }; // エネミーの参照
};
