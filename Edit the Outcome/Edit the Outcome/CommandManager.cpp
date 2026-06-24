#include "stdafx.h"
#include "CommandManager.hpp"

CommandManager::CommandManager()
{
	m_windowStack.push(MenuState::Base);
}

void CommandManager::SetData(std::vector<CommandData>& commandData)
{
	m_commandData = commandData;
	RegisterCommandName();
}

void CommandManager::RegisterCommandName()
{
	//　例外処理
	if (m_commandData.size() == 0)
	{
		throw Error{ U"要素が入っていません" };
	}

	// 容量を確保
	m_commandName.resize(m_commandData.size());

	// 名前の登録
	for (size_t i = 0; i < m_commandData.size(); i++)
	{
		m_commandName[i] = m_commandData[i].name;
	}
}

void CommandManager::ResetVariable()
{
	m_windowStack.push(MenuState::Base);
	m_baseCommandType = BaseCommandType::Attack;
}

void CommandManager::UpdateCommandProcess(const int32& maxIndex, int32& commandIndex, bool& isSelected)
{
	if (m_windowStack.top() == MenuState::Base)//ベースメニュー時
	{
		SelectBaseCommand(maxIndex, commandIndex, isSelected);
	}
	else if(m_windowStack.top() == MenuState::Skill)
	{
		SelectSkillCommand(commandIndex, isSelected);
	}
}

void CommandManager::SelectBaseCommand(const int32& maxIndex, int32& commandIndex, bool& isSelected)
{
	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyW.down())
	{
		//コマンドのインデックスを減らす
		commandIndex -= 1;

		//コマンドのインデックスが1未満にならないようにする
		if (commandIndex < 0)
		{
			commandIndex = 0;
		}
	}
	if (KeyS.down())
	{
		//コマンドのインデックスを増やす
		commandIndex += 1;

		//コマンドのインデクスが最大値より大きくならないようにする
		if (commandIndex > maxIndex - 1)
		{
			commandIndex = maxIndex - 1;
		}
	}

	// 現在のコマンドインデックス
	switch (commandIndex)
	{
	case 0: //攻撃
		m_baseCommandType = BaseCommandType::Attack;
		break;

	case 1: //防御
		m_baseCommandType = BaseCommandType::Diffence;
		break;

	case 2: //スキル
		m_baseCommandType = BaseCommandType::Skills;
		break;
	}

	// 各状態時の処理
	switch (m_baseCommandType)
	{
	case BaseCommandType::Attack: //攻撃選択時
		if (KeySpace.down())
		{
			isSelected = true; // 選択終了
		}
		break;
	case BaseCommandType::Diffence: //防御を選択時
		if (KeySpace.down())
		{
			commandIndex = 0;
			isSelected = true; // 選択終了
		}
		break;
	case BaseCommandType::Skills: //スキルを選択時
		if (KeySpace.down())
		{
			commandIndex = 0;
			m_windowStack.push(MenuState::Skill);
		}
		break;
	}
}

void CommandManager::SelectSkillCommand(int32& commandIndex, bool& isSelected)
{
	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyW.down())
	{
		//コマンドのインデックスを減らす
		commandIndex -= 1;

		//コマンドのインデックスが1未満にならないようにする
		if (commandIndex < 0)
		{
			commandIndex = 0;
		}
	}
	if (KeyS.down())
	{
		//コマンドのインデックスを増やす
		commandIndex += 1;

		// コマンドの要素数からコマンドのインデックスの最大値を決める
		int32 maxIndex = m_commandData.size() -1;

		//コマンドのインデックスが最大値より大きくならないようにする
		if (commandIndex > maxIndex)
		{
			commandIndex = maxIndex;
		}
	}

	if (KeySpace.down())
	{
		// 原状回復のためスタックをポップしてindexを0に設定
		m_windowStack.pop();
		commandIndex = 0;

		isSelected = true;
	}
	if (KeyB.down())
	{
		commandIndex = 0;
		//ベースのメニューへ戻る
		m_windowStack.pop();
	}
}


