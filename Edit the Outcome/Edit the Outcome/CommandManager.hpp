#pragma once
#include "CommandData.hpp"

/// <summary>
/// メニューステイト
/// 
/// ウィンドウメニューの状態を表す列挙型
///  </summary>
enum class MenuState
{
	Base,
	Skill
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

    /// @brief コマンドデータ内のコマンド名を配列として登録する関数
	void RegisterCommandName();

	/// @brief 変数をリセットする関数
	void ResetVariable();

	/// @brief コマンド処理を更新する関数
	void UpdateCommandProcess(const int32& maxIndex, int32& commandIndex, bool& isSelected);

	/// @brief ベースメニューのコマンドを選択する関数
	void SelectBaseCommand(const int32& maxIndex, int32& commandIndex, bool& isSelected);

	/// @brief スキルメニューのコマンドを選択する関数 
	void SelectSkillCommand(int32& commandIndex, bool& isSelected);

	bool GetIsSkillWindow()
	{
		if (m_windowStack.top() == MenuState::Skill)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/// @brief 
	std::vector<String> GetCommandName() { return m_commandName; }

private:
	BaseCommandType m_baseCommandType{ BaseCommandType::Attack };

	std::stack<MenuState> m_windowStack; //コマンドウィンドウのスタック

	std::vector<String> m_commandName; // コマンドの名前

	std::vector<CommandData> m_commandData; // コマンドデータの参照
	
};
