#include "stdafx.h"
#include "Enemy.hpp"

Enemy::Enemy(const EnemyData& masterData, int32 generate) : m_masterData(masterData), m_currentHp(masterData.maxHp)
{
	// ステータスの初期化
	m_currentHp = m_masterData.maxHp; 
	m_currentAtk = m_masterData.atk;

	// idを元にアセット名を設定
	switch (m_masterData.id)
	{
	case 1:
		m_assetName = U"Slime";
		break;
	case 2:
		m_assetName = U"Orc";
		break;
	}

	// 生成番号を設定
	m_generateNum = generate;
	// 描画位置を設定
	m_enemyPos.x = m_enemyPos.x + (200.0 * m_generateNum);
}

void Enemy::update()
{

	AnimationUpdate();
}

void Enemy::draw() const
{
	/// エネミー ///
	{
		TextureAsset(m_assetName)(Rect{ m_regionAtEnemy.x + (m_enemyAnimationNum * 200), m_regionAtEnemy.y,  m_regionAtEnemy.w, m_regionAtEnemy.h })
			.mirrored().drawAt(m_enemyPos);
	}
}

void Enemy::AnimationUpdate()
{
	// エネミーのアニメーションカウントが最大値以上になったら
    // アニメーションを更新する
	if (m_maxAnimationCount <= m_enemyAnimationCount)
	{
		m_enemyAnimationNum++;

		// アニメーション枚数が最大値以上になったら
		// アニメーションを振り出しに戻す
		if (m_maxAnimationNum <= m_enemyAnimationNum)
		{
			m_enemyAnimationNum = 0;
		}

		// アニメーションカウントをリセット
		m_enemyAnimationCount = 0;
	}
	m_enemyAnimationCount++;
}
