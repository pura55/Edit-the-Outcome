#include "stdafx.h"
#include "EnemyActionManager.hpp"
#include "HealthManager.hpp"
#include "Enemy.hpp"

EnemyActionManager::EnemyActionManager()
{
}

void EnemyActionManager::SetReference(HealthManager& healthManager, std::vector<Enemy*> enemies)
{
	m_healthManager = &healthManager;
	m_enemies = enemies;
}

void EnemyActionManager::SetEnemyQueue()
{
	for (auto* enemies : m_enemies)
	{
		m_enemiesQueue.push(enemies);
	}
}

void EnemyActionManager::ExecuteActionProcess(bool& isActed)
{
	// エネミーがダメージを受けている最中だったら一時的に処理を抜ける
	for (auto* enemies : m_enemies)
	{
		if(enemies->GetReceivingDamage()) return;
	}

	// キュー内の敵が全て輩出し終わったら行動を終了
	if (m_enemiesQueue.empty())
	{
		// フラグを行動済みに変更
		isActed = true;
		return;
	}

	// 倒されている場合このエネミーをポップする
	if (m_enemiesQueue.front()->GetIsDead())
	{
		m_enemiesQueue.pop();
		return;
	}

	if (m_enemiesQueue.front()->GetFinishedAttacking())
	{
		// プレイヤーにダメージを与える
		m_healthManager->EnemyAttackPlayer(m_enemiesQueue.front()->GetEnemyAtk());
		m_enemiesQueue.pop();
		return;
	}
	else
	{
		if (not m_enemiesQueue.front()->GetAttackingAnimation())
			m_enemiesQueue.front()->SetActionState(2); // 敵の行動状態を設定
	}
}
