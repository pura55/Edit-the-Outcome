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

void EnemyActionManager::ExecuteActionProcess(bool& isActed)
{
	for (auto* enemies : m_enemies)
	{
		// 倒されている場合このエネミーの処理を抜ける
		if (enemies->GetIsDead()) continue;

		// プレイヤーにダメージを与える
		m_healthManager->EnemyAttackPlayer(enemies->GetEnemyAtk());
	}

	// フラグを行動済みに変更
	isActed = true;
}
