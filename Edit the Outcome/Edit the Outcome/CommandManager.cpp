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
	RegistCommandData();
	InitExclusionEnemy();
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
		m_currentCommandData[commandDataNum].id = m_commandData[i].id;
		m_currentCommandData[commandDataNum].name = m_commandData[i].name;
		m_currentCommandData[commandDataNum].dmg = m_commandData[i].dmg;

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

void CommandManager::InitExclusionEnemy()
{
	m_exclusionEnemiesNum.resize(m_enemies.size());// 敵の配列のサイズをコピー

	// 除外する敵の番号に初期値として例外番号（-1）を格納
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		m_exclusionEnemiesNum[i] = -1;
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

	// 除外するターゲットを設定
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		if (m_enemies[i]->GetIsDead())
		{
			m_exclusionEnemiesNum[i] = m_enemies[i]->GetGenerateNum();
		}
	}

	bool decideMinEnemy = false;
	bool decideMaxEnemy = false;

	// 敵を除外後の最小値を設定
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		if (not decideMinEnemy)
		{
			// 除外設定がされていない場合その番号を最小値とする
			if (m_exclusionEnemiesNum[i] == -1)
			{
				m_minEnemiesNum = i; // iと生成番号が一致しているためiを代入
				m_targetSelectIndex = m_minEnemiesNum;  // 最小値をターゲットインデックスに適用
				decideMinEnemy = true; // 最小値設定完了
				break;
			}
		}
	}

	// 除外されていなかった場合最小値を0
	if (not decideMinEnemy)
	{
		m_minEnemiesNum = 0;
		m_targetSelectIndex = m_minEnemiesNum;
		decideMinEnemy = true;
	}

	// 敵を除外後の最大値を設定
	for (size_t i = m_exclusionEnemiesNum.size(); i > 0; i--)
	{
		size_t j = i - 1;

		if (not decideMaxEnemy)
		{
			// 除外設定がされていない場合その番号を最大値とする
			if (m_exclusionEnemiesNum[j] == -1)
			{
				m_maxEnemiesNum = j; // jと生成番号が一致しているためjを代入

				decideMaxEnemy = true; // 最大値設定完了
				break;
			}
		}
	}

	// 除外されていなかった場合最大値をサイズと同様
	if (not decideMaxEnemy)
	{
		m_maxEnemiesNum = m_exclusionEnemiesNum.size() - 1;
		decideMaxEnemy = true;
	}

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
	// 獲得してるコマンドがない場合は入力操作を行わない
	if (m_currentCommandData.size() != 0)
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
			int32 maxIndex = m_currentCommandData.size() - 1;

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

	// ターゲット選択が完了したら
	if (m_isTargetSelected)
	{
		// 選択矢印を非表示
		m_isShowArrow = false;

		// プレイヤーの攻撃が終了したタイミングでダメージを反映
		if (m_player->GetFinishedAttacking())
		{
			// ベースコマンドタイプによって関数の使用を分ける
			if (m_baseCommandType == BaseCommandType::Attack)
			{
				m_healthManager->PlayerAttackEnemy(m_player->GetPlayerAtk(), m_targetSelectIndex);
			}
			else if (m_baseCommandType == BaseCommandType::Skills)
			{
				// 選んだコマンドindexと対応するコマンドのダメージをターゲットに与える
				for (size_t i = 0; i < m_currentCommandData.size(); i++)
				{
					if (m_currentCommandIndex == i)
					{
						m_healthManager->PlayerAttackEnemy(m_currentCommandData[i].dmg, m_targetSelectIndex);
					}
				}
			}

			// コマンド選択終了
			isCommandSelected = true;
		}
		return;
	}

	// 選択矢印を表示
	m_isShowArrow = true;
	// ターゲットを選択する
	m_targetSelectSystem->TargetSelect(m_maxEnemiesNum, m_minEnemiesNum, m_exclusionEnemiesNum, m_targetSelectIndex, m_isTargetSelected, m_player);

	if (KeyC.down())
	{
		// 選択矢印を非表示
		m_isShowArrow = false;

		//一つ前のメニューへ戻る
		m_menuStack.pop();

		return;
	}
}


