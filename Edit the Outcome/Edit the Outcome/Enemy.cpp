#include "stdafx.h"
#include "Enemy.hpp"

Enemy::Enemy(const EnemyData& masterData, int32 generate) : m_masterData(masterData)
{
	// ステータスの初期化
	m_lifeState = EnemyLifeState::EnemyAlive;
	m_actionState = EnemyActionState::EnemyIdle;
	m_maxHp = m_masterData.maxHp;
	m_currentHp = m_masterData.maxHp;
	m_currentAtk = m_masterData.atk;
	m_maxAttackAnimationNum = m_masterData.spr_atk;
	m_attackAnimationHight = m_masterData.spr_height_atk;
	m_dmgAnimationHight = m_masterData.spr_height_dmg;
	m_deadAnimationHight = m_masterData.spr_height_dmg + 1;
	

	// idを元にアセット名を設定
	switch (m_masterData.id)
	{
	case 1:
		m_assetName = U"Slime";
		break;
	case 2:
		m_assetName = U"Orc";
		break;
	case 3:
		m_assetName = U"Bat";
		break;
	case 4:
		m_assetName = U"Skeleton";
		break;
	case 5:
		m_assetName = U"Werewolf";
		break;
	}

	// 生成番号を設定
	m_generateNum = generate;
	// 描画位置を設定
	m_characterPos.x = 750.0;
	m_characterPos.x = m_characterPos.x + (200.0 * m_generateNum);
}

void Enemy::update()
{
	switch (m_lifeState)
	{
	case EnemyLifeState::EnemyAlive:
		UpdateActionState();
		break;
	case EnemyLifeState::EnemyDead:
		break;
	}
	
}

void Enemy::draw() const
{
	/// エネミー ///
	{
		TextureAsset(m_assetName)(Rect{ m_regionAtEnemy.x + (m_animationNumX * 200), m_regionAtEnemy.y + (m_animationNumY * 200),  m_regionAtEnemy.w, m_regionAtEnemy.h })
			.mirrored().drawAt(m_characterPos);
	}
}

void Enemy::UpdateActionState()
{
	switch (m_actionState)
	{
	case EnemyActionState::EnemyIdle:
		// アニメーションの更新
		UpdateIdleAnimation();

		// 攻撃終了のフラグをfalse
		m_isFinishedAttacking = false;

		DeathProcess();
		break;
	case EnemyActionState::EnemyAttack:
		// 攻撃アニメーションを実行
		ExecuteAttackAnimation();
		break;
	case EnemyActionState::EnemyReceiveDamage:
		// 被ダメージアニメーションを実行
		ExecuteReceiveDamageAnimation();
		break;
	case EnemyActionState::EnemyDie:
		// 死亡アニメーションを実行
		ExecuteDeadAnimation();
		break;
	}
}

void Enemy::UpdateIdleAnimation()
{
	// Y軸のアニメーションを設定
	m_animationNumY = EnemyIdle;
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
	m_animationFrameCount += Scene::DeltaTime();
}

void Enemy::ExecuteAttackAnimation()
{
	if (not m_isAttackingAnimation)
	{
		// フレームカウントと各軸のアニメーションを設定
		m_animationFrameCount = 0;
		m_animationNumX = 0;
		m_animationNumY = m_attackAnimationHight;
		m_isAttackingAnimation = true;
	}
	// アニメーションフレームが最大値以上になったら
	// アニメーションを更新する
	if (m_maxAnimationFrame <= m_animationFrameCount)
	{
		m_animationNumX++;

		// アニメーション枚数が最大値以上になったら
		// エネミーの状態を待機状態へ
		if (m_maxAttackAnimationNum <= m_animationNumX)
		{
			m_animationNumX = m_maxAttackAnimationNum;
			m_actionState = EnemyActionState::EnemyIdle;
			m_isAttackingAnimation = false;
			m_isFinishedAttacking = true;
			return;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount += Scene::DeltaTime();
}

void Enemy::ExecuteReceiveDamageAnimation()
{
	if (not m_isReceivingDamage)
	{
		// フレームカウントと各軸のアニメーションを設定
		m_animationFrameCount = 0;
		m_animationNumX = 0;
		m_animationNumY = m_dmgAnimationHight;
		m_isReceivingDamage = true;
	}
	// アニメーションフレームが最大値以上になったら
	// アニメーションを更新する
	if (m_maxAnimationFrame <= m_animationFrameCount)
	{
		m_animationNumX++;

		// アニメーション枚数が最大値以上になったら
		// エネミーの状態を待機状態へ
		if (m_maxDamageAnimationNum <= m_animationNumX)
		{
			m_animationNumX = m_maxDamageAnimationNum;
			m_actionState = EnemyActionState::EnemyIdle;
			m_isReceivingDamage = false;
			// 死亡処理
			DeathProcess();
			return;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount += Scene::DeltaTime();
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
			m_lifeState = EnemyLifeState::EnemyDead;
			return;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount += Scene::DeltaTime();
}

void Enemy::DeathProcess()
{
	// 死亡フラグをtrue
	if (m_currentHp == 0 && !m_isDead)
	{
		m_isDead = true;
		// フレームカウントを0に設定
		m_animationFrameCount = 0;
		// 各軸のアニメーションを設定
		m_animationNumX = 0;
		m_animationNumY = m_deadAnimationHight;
	}

	if (m_isDead)
	{
		m_actionState = EnemyActionState::EnemyDie;
	}
}
