#include "stdafx.h"
#include "TargetSelectSystem.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

TargetSelectSystem::TargetSelectSystem() : m_exclusionEnemiesNum{}, m_enemies{}
{	
}

void TargetSelectSystem::SetReference(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies)
{
	// 参照を登録
	m_player = &player;
	m_enemies = &enemies;

	// 敵の参照が登録された際に除外の初期設定や最大値の設定も行う
	InitExclusionEnemies();
	// 最大値を初期化
	m_maxEnemiesNum = m_enemies->size() - 1;
}

void TargetSelectSystem::TargetSelect()
{
	if (KeySpace.down())
	{
		SetIsTargetSelected(true);
		// 状態を攻撃へ設定
		m_player->SetActionState(PlayerActionState::PlayerAttack);
		return;
	}

	// カーソル（矢印）を左に移動
	LeftCursor(m_minEnemiesNum, m_targetSelectIndex, m_exclusionEnemiesNum);

	// カーソル（矢印）を右に移動
	RightCursor(m_maxEnemiesNum, m_targetSelectIndex, m_exclusionEnemiesNum);
}

void TargetSelectSystem::TargetSelect(int32 skillID)
{
	if (KeySpace.down())
	{
		SetIsTargetSelected(true);

		// スキルIDによってアニメーションを変更
		switch (skillID)
		{
		case 1:
			// 状態をスキル１へ設定
			m_player->SetActionState(PlayerActionState::PlayerSkillFirst);
			break;
		case 2:
			// 状態をスキル２へ設定
			m_player->SetActionState(PlayerActionState::PlayerSkillSecond);
			break;
		}
		
		return;
	}

	// カーソル（矢印）を左に移動
	LeftCursor(m_minEnemiesNum, m_targetSelectIndex, m_exclusionEnemiesNum);

	// カーソル（矢印）を右に移動
	RightCursor(m_maxEnemiesNum, m_targetSelectIndex, m_exclusionEnemiesNum);
}

void TargetSelectSystem::InitExclusionEnemies()
{
	m_exclusionEnemiesNum.resize(m_enemies->size());// 敵の配列の容量をコピー

	// 除外する敵の番号に初期値として例外番号（-1）を格納
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		m_exclusionEnemiesNum[i] = -1;
	}
}

void TargetSelectSystem::ExclusionEnemies()
{
	// 除外するターゲットを設定
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		if ((*m_enemies)[i]->GetIsDead())
		{
			m_exclusionEnemiesNum[i] = (*m_enemies)[i]->GetGenerateNum();
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
		m_maxEnemiesNum = m_enemies->size() - 1;
		decideMaxEnemy = true;
	}
}
