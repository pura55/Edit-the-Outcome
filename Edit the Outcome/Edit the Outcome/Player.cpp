#include "stdafx.h"
#include "Player.hpp"

Player::Player(const PlayerProgressData& progress) : m_progress(progress)
{
	m_currentHp = m_progress.maxHp;
	m_currentAtk = m_progress.atk;
}
void Player::update()
{
	AnimationUpdate();
}

void Player::draw() const
{
	/// プレイヤー ///
	{
		TextureAsset(U"Swordsman")(Rect{ m_regionAtPlayer.x + (playerAnimationNum * 200), m_regionAtPlayer.y,  m_regionAtPlayer.w, m_regionAtPlayer.h }).drawAt(m_playerPos);
	}
}

void Player::AnimationUpdate()
{
	// プレイヤーのアニメーションカウントが最大値以上になったら
	// アニメーションを更新する
	if (maxAnimationCount <= playerAnimationCount)
	{
		playerAnimationNum++;

		// アニメーション枚数が最大値以上になったら
		// アニメーションを振り出しに戻す
		if (maxAnimationNum <= playerAnimationNum)
		{
			playerAnimationNum = 0;
		}

		// アニメーションカウントをリセット
		playerAnimationCount = 0;
	}
	playerAnimationCount++;
}
