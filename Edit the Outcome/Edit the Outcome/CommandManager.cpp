#include "stdafx.h"
#include "CommandManager.hpp"
#include "TargetSelectSystem.hpp"
#include "HealthManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

CommandManager::CommandManager()
{
	m_menuStack.push(MenuState::Default);
}

void CommandManager::SetReference(TargetSelectSystem& targetSelectSystem, HealthManager& healthManager, Player* player, std::vector<Enemy*> enemies)
{
	m_targetSelectSystem = &targetSelectSystem;
	m_healthManager = &healthManager;
	m_player = player;
	m_enemies = enemies;
}

void CommandManager::SetData(std::vector<CommandData>& commandData)
{
	m_commandData = commandData;
	RegistCommandName();
}

void CommandManager::RegistCommandName()
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
	// スタックがデフォルトになるまでpopする
	while (m_menuStack.top() != MenuState::Default)
	{
		m_menuStack.pop();
	}
	m_currentCommandIndex = 0;
	m_targetSelectIndex = 0;
	m_isTargetSelected = false;
}

void CommandManager::UpdateCommandProcess(bool& isCommandSelected)
{
	switch (m_menuStack.top())
	{
	case MenuState::Default:
		m_menuStack.push(MenuState::Base);
		break;
	case MenuState::Base: //ベースメニュー時
		SelectBaseCommand(isCommandSelected);
		break;
	case MenuState::Skill: //スキルメニュー時
		SelectSkillCommand(isCommandSelected);
		break;
	case MenuState::SelectEnemy: //敵選択時
		ManageDecisionProcessing(isCommandSelected);
		break;
	}
}

void CommandManager::SelectBaseCommand(bool& isCommandSelected)
{
	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyW.down())
	{
		//コマンドのインデックスを減らす
		m_currentCommandIndex -= 1;

		//コマンドのインデックスが0未満にならないようにする
		if (m_currentCommandIndex < 0)
		{
			m_currentCommandIndex = 0;
		}
	}
	if (KeyS.down())
	{
		//コマンドのインデックスを増やす
		m_currentCommandIndex += 1;

		//コマンドのインデクスが最大値より大きくならないようにする
		if (m_currentCommandIndex > m_baseMaxIndex)
		{
			m_currentCommandIndex = m_baseMaxIndex;
		}
	}

	// 現在のコマンドインデックス
	switch (m_currentCommandIndex)
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
			//isSelected = true; // 選択終了
			m_menuStack.push(MenuState::SelectEnemy);
		}
		break;
	case BaseCommandType::Diffence: //防御を選択時
		if (KeySpace.down())
		{
			m_currentCommandIndex = 0;
			isCommandSelected = true; // 選択終了
		}
		break;
	case BaseCommandType::Skills: //スキルを選択時
		if (KeySpace.down())
		{
			m_currentCommandIndex = 0;
			m_menuStack.push(MenuState::Skill);
		}
		break;
	}
}

void CommandManager::SelectSkillCommand(bool& isSelected)
{
	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyW.down())
	{
		//コマンドのインデックスを減らす
		m_currentCommandIndex -= 1;

		//コマンドのインデックスが0未満にならないようにする
		if (m_currentCommandIndex < 0)
		{
			m_currentCommandIndex = 0;
		}
	}
	if (KeyS.down())
	{
		//コマンドのインデックスを増やす
		m_currentCommandIndex += 1;

		// コマンドの要素数からコマンドのインデックスの最大値を決める
		int32 maxIndex = m_commandData.size() -1;

		//コマンドのインデックスが最大値より大きくならないようにする
		if (m_currentCommandIndex > maxIndex)
		{
			m_currentCommandIndex = maxIndex;
		}
	}

	if (KeySpace.down())
	{
		m_menuStack.push(MenuState::SelectEnemy);
	}
	if (KeyC.down())
	{
		m_currentCommandIndex = 0;
		//ベースのメニューへ戻る
		m_menuStack.pop();
	}
}

void CommandManager::ManageDecisionProcessing(bool& isCommandSelected)
{
	// 選択矢印を表示
	m_isShowArrow = true;
	// ターゲットを選択する
	m_targetSelectSystem->TargetSelect(m_maxEnemiesNum, m_targetSelectIndex, m_isTargetSelected);

	if (KeyC.down())
	{
		// 選択矢印を非表示
		m_isShowArrow = false;

		//一つ前のメニューへ戻る
		m_menuStack.pop();

		if (m_menuStack.top() == MenuState::Base)
		{
			return;
		}
		else
		{

		}

		return;
	}

	// ターゲット選択が完了したら
	if (m_isTargetSelected)
	{
		// ベースコマンドタイプによって関数の使用を分ける
		if (m_baseCommandType == BaseCommandType::Attack)
		{
			m_healthManager->PlayerAttackEnemy(m_player->GetPlayerAtk(), m_targetSelectIndex);
		}
		else if (m_baseCommandType == BaseCommandType::Skills)
		{
			// 選んだコマンドindexと対応するidのコマンドのダメージをターゲットに与える
			int32 selectCommandId = m_currentCommandIndex + 1;
			for (size_t i = 0; i < m_commandData.size(); i++)
			{
				if ( selectCommandId== m_commandData[i].id)
					m_healthManager->PlayerAttackEnemy(m_commandData[i].dmg, m_targetSelectIndex);
			}
		}

		// 選択矢印を非表示
		m_isShowArrow = false;

		// コマンド選択終了
		isCommandSelected = true;
	}
}


