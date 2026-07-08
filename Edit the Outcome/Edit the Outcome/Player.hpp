#pragma once
#include "PlayerProgressData.hpp"

/// <summary>
/// ライフステート
///
/// 生命に関する状態
/// </summary>
enum PlayerLifeState
{
	PlayerAlive, // 生きている状態
	PlayerDead   // 死亡状態
};

/// <summary>
/// アクションステート
///
/// 行動に関する状態
/// </summary>
enum PlayerActionState
{
	PlayerIdle = 0, // 待機
	PlayerAttack = 2, // 攻撃
	PlayerReceiveDamage = 5, // ダメージ受ける
	PlayerDie = 6 // 死亡
};

/// <summary>
/// プレイヤー
/// 
/// プレイヤーのインスタンスとして生成されるクラス
/// </summary>
class Player
{
public:
	Player(const PlayerProgressData& progress);
	void update();
	void draw() const;

	/// @brief 行動状態を更新する関数
	void UpdateActionState();

	/// @brief 待機アニメーションの更新処理を行う関数
	void UpdateIdleAnimation();

	/// @brief 攻撃アニメーションを実行する関数
	void ExecuteAttackAnimation();

	/// @brief 被ダメージアニメーションを実行する関数
	void ExecuteReceiveDamageAnimation();

	/// @brief 死亡アニメーションをする実行する関数
	void ExecuteDeadAnimation();

	Vec2 GetPlayerPos()const { return m_playerPos; }

	/// @brief アクションステートを設定する関数 
	void SetActionState(const int32 actionNum)
	{
		switch (actionNum)
		{
		case PlayerActionState::PlayerIdle:
			m_actionState = PlayerActionState::PlayerIdle;
			break;
		case PlayerActionState::PlayerAttack:
			m_actionState = PlayerActionState::PlayerAttack;
			break;
		case PlayerActionState::PlayerReceiveDamage:
			m_actionState = PlayerActionState::PlayerReceiveDamage;
			break;
		case PlayerActionState::PlayerDie:
			m_actionState = PlayerActionState::PlayerDie;
			break;
		}
	}

	/// HP関数 ///
#pragma region HP

	/// @brief 死亡処理を行う関数
	void DeathProcess();

	/// @brief 死亡フラグを返す関数
	bool GetIsDead() const { return m_isDead; }

	/// @brief 現在のプレイヤーのHpを取得する関数
	int32 GetPlayerHp()const { return m_currentHp; }

	/// @brief プレイヤーのhpを設定する関数
	void SetPlayerHp(int32 hp) { m_currentHp = hp; }

	/// @brief プレイヤーのHpの割合を計算する関数
	/// @details (詳)PctはPercentageの略です 
	int32 CalculatePctOfHp()
	{
		playerHealthPct = fullHealthPct * (m_currentHp / m_maxHp);
		return playerHealthPct;
	}

#pragma endregion

	/// ATK関数 ///
#pragma region ATK

	/// @brief プレイヤーのAtkを取得す関数
	int32 GetPlayerAtk()const { return m_currentAtk; }

	/// @brief プレイヤーのAtkを設定する関数
	void SetPlayerAtk(int32 atk) { m_currentAtk = atk; }

	/// @brief 攻撃が終了したかどうかを返す関数
	bool GetFinishedAttacking()const { return m_isFinishedAttacking; }
#pragma endregion
    
private:

	/// 描画変数 ///
#pragma region draw

	const int32 m_maxAnimationFrame{ 25 }; // アニメーションフレームの最大値

	const int32 m_maxAnimationNum{ 6 };    // アニメーションの最大枚数

	const int32 m_maxAttackAnimationNum{ 6 }; // 攻撃アニメーションの最大枚数

	const int32 m_maxDamageAnimationNum{ 4 }; // 被ダメージアニメーションの最大枚数

	const int32 m_maxDeadAnimationNum{ 3 }; // 死亡アニメーションの最大枚数

	Vec2 m_playerPos{ 400.0, 400.0 };        // プレイヤーの座標

	Rect m_regionAtPlayer{ 0, 0, 200, 200 }; // 画像取得範囲

	int32 m_animationFrameCount{ 0 };   // アニメーションフレームのカウンター

	int32 m_animationNumX{ 0 };  // X軸のアニメーション枚数

	int32 m_animationNumY{ 0 };  // Y軸のアニメーション枚数

	bool m_nowAttackingAnimation{ false }; // 攻撃アニメーションの最中かどうか

	/// ステータス変数 ///
#pragma region status

	PlayerLifeState m_lifeState; // 生死の状態

	PlayerActionState m_actionState; // 行動の状態
	
	const int32 fullHealthPct{ 100 };        // 体力の最大割合
	
	int32 playerHealthPct{ fullHealthPct };  // プレイヤーの割合

	double m_maxHp;                           // 最大体力：体力の割合を計算するためdouble型

	int32 m_currentHp;                       // 現在の体力

	int32 m_currentAtk;                      // 現在の攻撃力

	PlayerProgressData m_progress;   // プレイヤーのデータ保持

	bool m_isFinishedAttacking{ false }; // 攻撃が終了したかどうか

	bool m_isReceivedDamage{ false }; // ダメージを受けたかどうかのフラグ

	bool m_isDead{ false };  // 死亡フラグ

#pragma endregion


};

	
	
