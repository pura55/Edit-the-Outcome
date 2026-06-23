#include "stdafx.h"
#include "HealthManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

HealthManager::HealthManager()
{
}

void HealthManager::SetReference(Player* player, std::vector<Enemy*> enemy)
{
	m_player = player;
	m_enemies = enemy;
}

void HealthManager::PlayerAttackEnemy(int32 playerAtk, int32 enemyHp, int32 enemyGenerateNum)
{
	// エネミーのHpを修正
	int32 replaceEnemyHp = enemyHp - playerAtk;
	// 0以下の場合0に設定
	if (enemyHp <= 0) replaceEnemyHp = 0;

	// 生成番号から特定のエネミーを探してHpを設定
	for (auto* enemies : m_enemies)
	{
		if (enemies->GetGenerateNum() == enemyGenerateNum)
		{
			// エネミーのHpを設定
			enemies->SetEnemyHp(replaceEnemyHp);
		}
	}
}

void HealthManager::EnemyAttackPlayer(int32 enemyAtk, int32 playerHp)
{
	// プレイヤーのHpを修正
	int32 replacePlayerHp = playerHp - enemyAtk;
	// 0以下の場合0に設定
	if (playerHp <= 0) replacePlayerHp = 0;

	// プレイヤーのHpを設定
	m_player->SetPlayerHp(replacePlayerHp);
}
