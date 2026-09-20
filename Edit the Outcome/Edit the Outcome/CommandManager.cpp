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

void CommandManager::update()
{
	switch (m_menuStack.top())
	{
	case MenuState::Default:
		m_menuStack.push(MenuState::Base);
		break;
	case MenuState::Base: //ベースメニュー時
		SelectBaseCommand();
		break;
	case MenuState::Skill: //スキルメニュー時
		SelectSkillCommand();
		break;
	case MenuState::SelectEnemy: //敵選択時
		ManageDecisionProcessing();
		break;
	}
}

void CommandManager::SetReference(TargetSelectSystem& targetSelectSystem, HealthManager& healthManager, Player& player)
{
	m_targetSelectSystem = &targetSelectSystem;
	m_healthManager = &healthManager;
	m_player = &player;
}

void CommandManager::SetData(std::vector<CommandData>& commandData)
{
	m_commandData = commandData;
	RegistCommandData();
}

void CommandManager::RegistCommandData()
{
	//　例外処理
	if (m_commandData.size() == 0)
	{
		throw Error{ U"要素が入っていません" };
	}

	int32 currentGetCommand = 0; // 現在獲得しているコマンドの個数

	// 獲得しているコマンドがある場合個数を増やす
	for (size_t i = 0; i < m_commandData.size(); i++)
	{
		if (m_commandData[i].isGet == false) continue;

		currentGetCommand++;
	}

	// 容量を確保
	m_currentCommandData.resize(currentGetCommand);

	int32 commandDataNum = 0;// 格納するコマンドデータの番号

	// 名前の登録
	for (size_t i = 0; i < m_commandData.size(); i++)
	{
		if (m_commandData[i].isGet == false) continue;

		// 獲得している各データを格納
		m_currentCommandData[commandDataNum] = m_commandData[i];

		commandDataNum++;
	}

	// コマンド名の配列のサイズを確保
	m_commandName.resize(m_currentCommandData.size());

	// 現在獲得してるコマンドデータから名前を格納
	for (size_t i = 0; i < m_commandName.size(); i++)
	{
		m_commandName[i] = m_currentCommandData[i].name;
	}
}

void CommandManager::ResetVariable()
{
	// ターゲットの除外処理を実行
	m_targetSelectSystem->ExclusionEnemies();

	// 変数を初期状態に設定
	m_currentCommandIndex = 0;
	m_targetSelectSystem->SetIsTargetSelected(false);
}

void CommandManager::PopMenuState()
{
	// スタックがデフォルトになるまでpopする
	while (m_menuStack.top() != MenuState::Default)
	{
		m_menuStack.pop();
	}
}

void CommandManager::SelectBaseCommand()
{
	// カーソル上昇
	UpCursor(/*最小値*/ 0, m_currentCommandIndex);

	// カーソル下降
	DownCursor(m_baseMaxIndex, m_currentCommandIndex);

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
			m_menuStack.push(MenuState::SelectEnemy);
		}
		break;
	case BaseCommandType::Diffence: //防御を選択時
		if (KeySpace.down())
		{
			m_player->AddDefense();
			m_currentCommandIndex = 0;
			SetIsCommandSelected(true); // 選択終了
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

void CommandManager::SelectSkillCommand()
{
	// 獲得してるコマンドがない場合は入力操作を行わない
	if (m_currentCommandData.size() != 0)
	{
		// カーソル上昇
		UpCursor(/*最小値*/ 0, m_currentCommandIndex);

		// カーソル下降
		DownCursor(m_currentCommandData.size(), m_currentCommandIndex);

		if (KeySpace.down())
		{
			m_menuStack.push(MenuState::SelectEnemy);
		}
	}
	
	if (KeyC.down())
	{
		m_currentCommandIndex = 0;
		//ベースのメニューへ戻る
		m_menuStack.pop();
	}
}

void CommandManager::ManageDecisionProcessing()
{

	// ターゲット選択が完了したら
	if (m_targetSelectSystem->GetIsTargetSelected())
	{
		// 選択矢印を非表示
		m_isShowArrow = false;

		// ダメージ反映
		if (DamageReflection())
		{
			// コマンド選択終了
			SetIsCommandSelected(true);
		}
		
		return;
	}

	m_maxEnemiesNum = m_targetSelectSystem->GetMaxNum();

	// 選択矢印を表示
	m_isShowArrow = true;

	// ターゲット選択
	SelectTarget();


	if (KeyC.down())
	{
		// 選択矢印を非表示
		m_isShowArrow = false;

		//一つ前のメニューへ戻る
		m_menuStack.pop();

		return;
	}
}

bool CommandManager::DamageReflection()
{
	// プレイヤーの攻撃が終了したタイミングでダメージを反映
	if (m_player->GetFinishedAttacking())
	{
		// ベースコマンドタイプによって関数の使用を分ける
		if (m_baseCommandType == BaseCommandType::Attack)
		{
			// ダメージ反映
			m_healthManager->PlayerAttackEnemy(m_player->GetPlayerAtk(), m_targetSelectSystem->GetSelectTarget());
			return true;
		}
		else if (m_baseCommandType == BaseCommandType::Skills)
		{
			// スキルのダメージ反映が終了していたら
			if (DamageReflectionSkill())
			{
				return true;
			}
		}
	}

	return false;
}

bool CommandManager::DamageReflectionSkill()
{
	// 選んだコマンドindexと対応するコマンドのダメージをターゲットに与える
	for (size_t i = 0; i < m_currentCommandData.size(); i++)
	{
		// コマンドが違っていたら次の処理へ
		if (m_currentCommandIndex != i) continue;

		m_healthManager->PlayerSkillEnemy(m_currentCommandData[i].dmg, m_targetSelectSystem->GetSelectTarget(), m_currentCommandData[i].skillNums);

		// 使用したコマンドを削除（現在は一度きりの使用）
		m_currentCommandData.erase(m_currentCommandData.begin() + i);

		m_commandName.erase(m_commandName.begin() + i);
		return true;
	}
	return false;
}

void CommandManager::SelectTarget()
{
	// ベースコマンドタイプによって関数の使用を分ける
	if (m_baseCommandType == BaseCommandType::Attack)
	{
		// ターゲットを選択する
		m_targetSelectSystem->TargetSelect();
	}
	else if (m_baseCommandType == BaseCommandType::Skills)
	{
		// ターゲットを選択する
		m_targetSelectSystem->TargetSelect(m_currentCommandData[m_currentCommandIndex].id);
	}
}


