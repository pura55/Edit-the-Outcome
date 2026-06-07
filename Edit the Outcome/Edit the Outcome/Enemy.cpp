#include "stdafx.h"
#include "Enemy.hpp"

Enemy::Enemy(const EnemyData& masterData) : m_masterData(masterData), m_currentHp(masterData.maxHp)
{
	//ステータスの初期化
	m_currentHp = m_masterData.maxHp; 
	m_currentAtk = m_masterData.atk;
}

void Enemy::update()
{

	AnimationUpdate();
}

void Enemy::draw() const
{
	/// エネミー ///
	{
		TextureAsset(U"Orc")(Rect{ m_regionAtEnemy.x + (enemyAnimationNum * 200), m_regionAtEnemy.y,  m_regionAtEnemy.w, m_regionAtEnemy.h }).mirrored().drawAt(m_enemyPos);
	}
}

void Enemy::AnimationUpdate()
{
	// エネミーのアニメーションカウントが最大値以上になったら
    // アニメーションを更新する
	if (maxAnimationCount <= enemyAnimationCount)
	{
		enemyAnimationNum++;

		// アニメーション枚数が最大値以上になったら
		// アニメーションを振り出しに戻す
		if (maxAnimationNum <= enemyAnimationNum)
		{
			enemyAnimationNum = 0;
		}

		// アニメーションカウントをリセット
		enemyAnimationCount = 0;
	}
	enemyAnimationCount++;
}
