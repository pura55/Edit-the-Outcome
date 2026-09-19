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
		m_statusUI.draw(m_player, m_enemies);
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
		// 空出ないとき
		if (not m_damageDisplay.empty())
		{
			// ダメージ表示
			for (auto& damage : m_damageDisplay)
			{
				damage.draw();
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

void BattleUI::SetReference(BattleSystem& battleSystem,CommandManager& commandManager,TargetSelectSystem& targetSelectSystem, Player* player, const std::vector<Enemy*>& enemy)
{
	m_battleSystem = &battleSystem;
	m_commandManager = &commandManager;
	m_targetSelectSystem = &targetSelectSystem;
	m_player = player;
	m_enemies = enemy;
}

void BattleUI::DamageInQueue()
{
	for (int32 i = 0; i < m_damageDisplayNumbers; i++)
	{
		// ダメージ表示をインキュー
		m_damageDisplayQueue.push(DamageDisplay());
	}
}

void BattleUI::UpdateDamageDisplays()
{
	// 空ではない場合
	if (not m_damageDisplay.empty())
	{
		for (size_t i = 0; i < m_damageDisplay.size(); i++)
		{
			m_damageDisplay[i].update();
		}
	}
}

void BattleUI::PassDamageQueue(int32 damage, Vec2 position)
{
	// キューの先頭にダメージを渡す
	m_damageDisplayQueue.front().SetInformation(damage, position);

	// 配列にキューの先頭を譲渡する
	m_damageDisplay.push_back(std::move(m_damageDisplayQueue.front()));

	// キューをポップ
	m_damageDisplayQueue.pop();
}

void BattleUI::PassDamageQueue(int32 damage, Vec2 position, int32 skillNums)
{
	// キューの先頭にダメージを渡す
	m_damageDisplayQueue.front().SetInformation(damage, position, skillNums);

	// 配列にキューの先頭を譲渡する
	m_damageDisplay.push_back(std::move(m_damageDisplayQueue.front()));

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
			// 時間が終了していない場合次の処理へ
			if (not m_damageDisplay[i].DecreaseLeftTime()) continue;

			// キューに表示が終了したダメージ表示をインキュー（譲渡）
			m_damageDisplayQueue.push(std::move(m_damageDisplay[i]));

			// 渡した要素を削除
			m_damageDisplay.erase(m_damageDisplay.begin() + i);
		}
	}
}

