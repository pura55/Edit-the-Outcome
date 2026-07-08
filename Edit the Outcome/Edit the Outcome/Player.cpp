#include "stdafx.h"
#include "Player.hpp"

Player::Player(const PlayerProgressData& progress) : m_progress(progress)
{
	// ステータスの初期化
	m_lifeState = PlayerLifeState::PlayerAlive;
	m_actionState = PlayerActionState::PlayerIdle;
	m_maxHp = m_progress.maxHp;
	m_currentHp = m_progress.maxHp;
	m_currentAtk = m_progress.atk;
}
void Player::update()
{
	switch (m_lifeState)
	{
	case PlayerLifeState::PlayerAlive:
		UpdateActionState();
		break;
	case PlayerLifeState::PlayerDead:
		break;
	}
}

void Player::draw() const
{
	/// プレイヤー ///
	{
		TextureAsset(U"Swordsman")(Rect{ m_regionAtPlayer.x + (m_animationNumX * 200), m_regionAtPlayer.y + (m_animationNumY * 200),  m_regionAtPlayer.w, m_regionAtPlayer.h }).drawAt(m_playerPos);
	}
}

void Player::UpdateActionState()
{
	switch (m_actionState)
	{
	case PlayerActionState::PlayerIdle:
		// アニメーションの更新
		UpdateIdleAnimation();

		// 攻撃終了フラグをfalse
		m_isFinishedAttacking = false;

		DeathProcess();
		break;
	case PlayerActionState::PlayerAttack:
		// 攻撃アニメーションを実行
		ExecuteAttackAnimation();
		break;
	case PlayerActionState::PlayerReceiveDamage:
		// 被ダメージアニメーションを実行
		ExecuteReceiveDamageAnimation();
		break;
	case PlayerActionState::PlayerDie:
		// 死亡アニメーションを実行
		ExecuteDeadAnimation();
		break;
	}
}

void Player::UpdateIdleAnimation()
{
	// Y軸のアニメーションを設定
	m_animationNumY = PlayerIdle;
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

void Player::ExecuteAttackAnimation()
{
	if (not m_nowAttackingAnimation)
	{
		// フレームカウントと各軸のアニメーションを設定
		m_animationFrameCount = 0;
		m_animationNumX = 0;
		m_animationNumY = PlayerAttack;
		m_nowAttackingAnimation = true;
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
			m_actionState = PlayerActionState::PlayerIdle;
			m_nowAttackingAnimation = false;
			m_isFinishedAttacking = true;
			return;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount++;
}

void Player::ExecuteReceiveDamageAnimation()
{
	if (not m_isReceivedDamage)
	{
		// フレームカウントと各軸のアニメーションを設定
		m_animationFrameCount = 0;
		m_animationNumX = 0;
		m_animationNumY = PlayerReceiveDamage;
		m_isReceivedDamage = true;
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
			m_actionState = PlayerActionState::PlayerIdle;
			m_isReceivedDamage = false;
			// 死亡処理
			DeathProcess();
			return;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount++;
}

void Player::ExecuteDeadAnimation()
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
			m_lifeState = PlayerLifeState::PlayerDead;
			return;
		}

		// フレームカウントをリセット
		m_animationFrameCount = 0;
	}
	m_animationFrameCount++;
}

void Player::DeathProcess()
{
	// 死亡フラグをtrue
	if (m_currentHp == 0 && !m_isDead)
	{
		m_isDead = true;
		// フレームカウントを0に設定
		m_animationFrameCount = 0;
		// 各軸のアニメーションを設定
		m_animationNumX = 0;
		m_animationNumY = PlayerDie;
	}

	if (m_isDead)
	{
		m_actionState = PlayerActionState::PlayerDie;
	}
}

