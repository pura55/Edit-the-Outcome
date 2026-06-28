#include "stdafx.h"
#include "HealthManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

HealthManager::HealthManager()
{
}

void HealthManager::SetReference(Player* player, std::vector<Enemy*> enemies)
{
	m_player = player;
	m_enemies = enemies;
}

void HealthManager::PlayerAttackEnemy(int32 playerAtk, int32 enemyGenerateNum)
{
	// 生成番号から特定のエネミーを探してHpを設定
	for (auto* enemies : m_enemies)
	{
		if (enemies->GetGenerateNum() == enemyGenerateNum)
		{
			// エネミーのHpを修正
			int32 replaceEnemyHp = enemies->GetEnemyHp() - playerAtk;
			// 0以下の場合0に設定
			if (replaceEnemyHp < 0) replaceEnemyHp = 0;
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
