#include "stdafx.h"
#include "Enemy.hpp"

Enemy::Enemy(const EnemyData& masterData, int32 generate) : m_masterData(masterData), m_currentHp(masterData.maxHp)
{
	// ステータスの初期化
	enemyState = EnemyState::Alive;
	m_maxHp = m_masterData.maxHp;
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
	switch (enemyState)
	{
	case EnemyState::Alive:
		// アニメーションの更新
		AnimationUpdate();

		// 死亡処理
		DeathProcess();
		break;

	case EnemyState::Dead:
		break;
	}
	
}

void Enemy::draw() const
{
	/// エネミー ///
	{
		TextureAsset(m_assetName)(Rect{ m_regionAtEnemy.x + (m_animationNumX * 200), m_regionAtEnemy.y + (m_animationNumY * 200),  m_regionAtEnemy.w, m_regionAtEnemy.h })
			.mirrored().drawAt(m_enemyPos);
	}
}

void Enemy::AnimationUpdate()
{
	// アニメーションフレームが最大値以上になったら
    // アニメーションを更新する
	if (m_maxAnimationFrame <= m_animationFrameCount)
	{
		m_animationNumX++;

		// アニメーション枚数が最大値以上になったら
		// アニメーションを振り出しに戻す
		if (m_maxAnimationNum <= m_animationNumX)
		{
			m_animationNumX = 0;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount++;
}

void Enemy::ExecuteDeadAnimation()
{
	// アニメーションフレームが最大値以上になったら
	// アニメーションを更新する
	if (m_maxAnimationFrame <= m_animationFrameCount)
	{
		m_animationNumX++;

		// アニメーション枚数が最大値以上になったら
		// エネミーの状態を死亡状態へ
		if (m_maxDeadAnimationNum <= m_animationNumX)
		{
			m_animationNumX = m_maxDeadAnimationNum;
			enemyState = EnemyState::Dead;
			return;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount++;
}

void Enemy::DeathProcess()
{
	// 死亡フラグをtrue
	if (m_currentHp == 0 && !m_isDead)
	{
		m_isDead = true;
		// フレームカウントを0に設定
		m_animationFrameCount = 0;
		// Y軸のアニメーションを設定
		m_animationNumY = 5;
	}

	if (m_isDead)
	{
		// 死亡アニメーションを実行
		ExecuteDeadAnimation();
	}
}
