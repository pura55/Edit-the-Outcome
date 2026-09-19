#pragma once
#include "Selector.hpp"
#include "CommandData.hpp"

// 前方宣言
class TargetSelectSystem;
class HealthManager;
class Player;
class Enemy;

/// <summary>
/// メニューステイト
/// 
/// ウィンドウメニューの状態を表す列挙型
/// </summary>
enum class MenuState
{
	Default,     // デフォルトで何も表示しない
	Base,        // ベースメニュー
	Skill,       // スキルメニュー
	SelectEnemy  // 敵選択画面
};

/// <summary>
/// ベースコマンドタイプ
/// </summary>
enum class BaseCommandType
{
	Attack,    // 攻撃
	Diffence,  // 守備
	Skills     // スキル
};

/// <summary>
/// コマンドマネージャー
///
/// コマンド操作を管理するクラス
/// Selectorを継承
/// </summary>
class CommandManager : public Selector
{
public:
	CommandManager();

	void update();

	/// @brief コマンドデータの参照を設定する関数
	void SetData(std::vector<CommandData>& commandData);

	/// @brief 参照を登録する関数
	void SetReference(TargetSelectSystem& targetSelectSystem, HealthManager& healthManager, Player* player, std::vector<Enemy*>& enemies);

    /// @brief コマンドデータ内の処理に必要な各データを配列として登録する関数
	void RegistCommandData();

	/// @brief 変数をリセットする関数
	void ResetVariable();

	/// @brief メニューステートをポップする関数
	void PopMenuState();

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

	/// @brief スキルウィンドウを表示できる状態かどうかを返す関数
	/// @return true:可能 false:不可能
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

	/// @brief isShowArrowを取得する関数
	bool GetIsShowArrow() { return m_isShowArrow; }

	/// @brief コマンドの名前を返す関数
	std::vector<String> GetCommandName()
	{
		return m_commandName;
	}

	/// @brief コマンド選択フラグを返す関数	
	bool GetIsCommandSelected() const { return m_isCommandSelected; }

	/// @brief 
	/// @param selected 設定するフラグ
	void SetIsCommandSelected(bool selected) { m_isCommandSelected = selected; }


private:
	/// @brief ベースメニューのコマンドを選択する関数
	void SelectBaseCommand();

	/// @brief スキルメニューのコマンドを選択する関数 
	void SelectSkillCommand();

	/// @brief コマンドの決定処理を管理する関数
	void ManageDecisionProcessing();

	/// @brief ダメージを反映させる関数
	bool DamageReflection();

	/// @brief ダメージを反映させる関数(スキルver)
	bool DamageReflectionSkill();

	void SelectTarget();

private:

	/// 列挙体 ///
	BaseCommandType m_baseCommandType{ BaseCommandType::Attack };

	/// 一般変数 ///

	const int32 m_baseMaxIndex{ 2 }; // ベースメニューのコマンドの最大値
	
	int32 m_currentCommandIndex{ 0 }; // 現在選択されているコマンドのインデックス

	bool m_isTargetSelected{ false };  // ターゲットの選択がされているかどうかのフラグ

	int32 m_maxEnemiesNum{ 0 }; // エネミーの最大数（死んでいた場合繰りさげで最大を入れ替える）

	bool m_isShowArrow{ false }; // 矢印をみせるかどうかのフラグ

	bool m_isCommandSelected{ false }; // 選択フラグ

	/// 構造体 ///
	std::stack<MenuState> m_menuStack; //コマンドウィンドウのスタック

	std::vector<CommandData> m_currentCommandData; // 現在のコマンドデータ

	std::vector<String> m_commandName; // コマンドの名前


	/// 参照 ///
	std::vector<CommandData> m_commandData; // コマンドデータの参照

	TargetSelectSystem* m_targetSelectSystem{ nullptr }; // ターゲットセレクトシステムの参照

	HealthManager* m_healthManager{ nullptr }; // ヘルスマネージャーの参照

	Player* m_player{ nullptr }; // プレイヤーの参照

	std::vector<Enemy*> m_enemies; // エネミーの参照
};
