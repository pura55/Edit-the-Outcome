#include "stdafx.h"
#include "BattleUI.hpp"
#include "BattleSystem.hpp"
#include "CommandManager.hpp"
#include "TargetSelectSystem.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

BattleUI::BattleUI() :m_player{ nullptr }
{
	DamageInQueue();
}

void BattleUI::update()
{
	m_commandWindow.update(m_commandManager);

	UpdateDamageDisplays();

	ReturnDamageQueue();

	// 結果が出たときに更新
	if (m_isWin or m_isLose)m_result.update();
}


void BattleUI::draw() const
{
	/// ステータス ///
	{
		m_statusUI.draw(*m_player, *m_enemies);
	}
	

	/// コマンドウィンドウ ///
	{
		m_commandWindow.draw(m_commandManager);
	}

	/// 敵を選択する矢印 ///
	{
		m_selectArrow.draw(m_commandManager, m_targetSelectSystem);
	}

	{
		// 空ではないとき
		if (not m_damageDisplay.empty())
		{
			// ダメージ表示
			for (auto& damage : m_damageDisplay)
			{
				// 表示フラグがtureの場合
				if (damage->GetIsShow()) damage->draw();;
			}
		}
	}

	// 結果
	{
		if (m_isWin)
		{
			m_result.draw(true);
		}
		else if (m_isLose)
		{
			m_result.draw(false);
		}
	}
}

void BattleUI::SetReference(BattleSystem& battleSystem,CommandManager& commandManager,TargetSelectSystem& targetSelectSystem, Player& player, std::vector<std::unique_ptr<Enemy>>& enemies)
{
	m_battleSystem = &battleSystem;
	m_commandManager = &commandManager;
	m_targetSelectSystem = &targetSelectSystem;
	m_player = &player;
	m_enemies = &enemies;
}

void BattleUI::DamageInQueue()
{

	for (int32 i = 0; i < m_damageDisplayNumbers; i++)
	{
		// 生成
		m_damageDisplay.push_back(std::make_unique<DamageDisplay>());
	}

	for (auto& disp : m_damageDisplay)
	{
		// ダメージ表示をインキュー
		m_damageDisplayQueue.push(disp.get());
	}
}

void BattleUI::UpdateDamageDisplays()
{
	// 空ではない場合
	if (not m_damageDisplay.empty())
	{
		for (size_t i = 0; i < m_damageDisplay.size(); i++)
		{
			if(not m_damageDisplay[i]->GetIsShow()) continue;

			m_damageDisplay[i]->update();
		}
	}
}

void BattleUI::ShowDamage(int32 damage, Vec2 position)
{
	// 空ではない場合
	if (m_damageDisplayQueue.empty()) { return; }

	// キューの先頭にダメージを渡す
	m_damageDisplayQueue.front()->SetInformation(damage, position);

	// フラグをture
	m_damageDisplayQueue.front()->SetIsShow(true);

	// キューをポップ
	m_damageDisplayQueue.pop();
}

void BattleUI::ShowDamage(int32 damage, Vec2 position, int32 skillNums)
{
	// 空ではない場合
	if (m_damageDisplayQueue.empty()) { return; }

	// キューの先頭にダメージを渡す
	m_damageDisplayQueue.front()->SetInformation(damage, position, skillNums);

	// フラグをture
	m_damageDisplayQueue.front()->SetIsShow(true);

	// キューをポップ
	m_damageDisplayQueue.pop();
}

void BattleUI::ReturnDamageQueue()
{
	// 空ではない場合
	if (not m_damageDisplay.empty())
	{
		for (size_t i = 0; i < m_damageDisplay.size(); i++)
		{
			// 非表示の場合は次の処理へ
			if (not m_damageDisplay[i]->GetIsShow()) continue;

			// 時間が終了していない場合次の処理へ
			if (not m_damageDisplay[i]->DecreaseLeftTime()) continue;

			// 非表示
			m_damageDisplay[i]->SetIsShow(false);

			// キューに表示が終了したダメージ表示をインキュー（譲渡）
			m_damageDisplayQueue.push(m_damageDisplay[i].get());

			// 時間をリセット
			m_damageDisplay[i]->ResetLeftTime();
		}
	}
}

