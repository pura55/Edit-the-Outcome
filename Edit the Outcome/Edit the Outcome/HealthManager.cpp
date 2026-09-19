#include "stdafx.h"
#include "HealthManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "BattleUI.hpp"

HealthManager::HealthManager()
{
}

void HealthManager::SetReference(Player* player, const std::vector<Enemy*>& enemies, BattleUI& battleUI)
{
	m_player = player;
	m_enemies = enemies;
	m_battleUI = &battleUI;
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

			// 行動状態を被ダメージに設定
			enemies->SetActionState(4);

			// ダメージ表示
			m_battleUI->PassDamageQueue(playerAtk, enemies->GetPosition());

			break;
		}
	}
}

void HealthManager::PlayerSkillEnemy(int32 playerAtk, int32 enemyGenerateNum, int32 skillNums)
{
	// 生成番号から特定のエネミーを探してHpを設定
	for (auto* enemies : m_enemies)
	{
		if (enemies->GetGenerateNum() == enemyGenerateNum)
		{
			// 攻撃回数分ダメージ反映
			for (int32 i = 0; i < skillNums; i++)
			{
				// エネミーのHpを修正
				int32 replaceEnemyHp = enemies->GetEnemyHp() - playerAtk;

				// 0以下の場合0に設定
				if (replaceEnemyHp < 0) replaceEnemyHp = 0;

				// エネミーのHpを設定
				enemies->SetEnemyHp(replaceEnemyHp);

				// 行動状態を被ダメージに設定
				enemies->SetActionState(4);

				// ダメージ表示
				m_battleUI->PassDamageQueue(playerAtk, enemies->GetPosition(), i);
			}
			break;
		}
	}
}

void HealthManager::EnemyAttackPlayer(int32 enemyAtk)
{
	// 現在の守備力
	int32 playerDefense = m_player->GetPlayerDefense();

	// ダメージ
	int32 damage = enemyAtk;

	// 守備力がある場合
	if (playerDefense > 0)
	{
		// 守備力がダメージより多きい場合
		if ((damage < playerDefense))
		{
			// 守備力からダメージを減算
			playerDefense = playerDefense - damage;

			// 守備力を再設定
			m_player->SetPlayerDefense(playerDefense);

			// ダメージを０に設定
			damage = 0;
		}
		else
		{
			// ダメージから守備力を減算
			damage = damage - playerDefense;

			// 守備力を0に設定
			m_player->SetPlayerDefense(0);
		}
		
	}
	

	// プレイヤーのHpを修正
	int32 replacePlayerHp = m_player->GetPlayerHp() - damage;
	// 0以下の場合0に設定
	if (replacePlayerHp <= 0) replacePlayerHp = 0;

	// プレイヤーのHpを設定
	m_player->SetPlayerHp(replacePlayerHp);

	// 行動状態を被ダメージに設定
	m_player->SetActionState(5);

	// ダメージ表示
	m_battleUI->PassDamageQueue(damage, m_player->GetPosition());
}
