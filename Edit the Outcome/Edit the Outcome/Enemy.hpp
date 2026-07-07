#pragma once
#include "EnemyData.hpp"

/// <summary>
/// ライフステート
///
/// 生命に関する状態
/// </summary>
enum LifeState
{
	Alive, // 生きている状態
	Dead   // 死亡状態
};

/// <summary>
/// アクションステート
///
/// 行動に関する状態
/// </summary>
enum ActionState
{
	Idle = 0, // 待機
	Attack = 2, // 攻撃
	ReceiveDamage = 4, // ダメージ受ける
	Die = 5
};

/// <summary>
/// エネミー
/// 
/// エネミーのインスタンスとして生成されるクラス
/// </summary>
class Enemy
{
public:
	Enemy(const EnemyData& masterData, int32 generate);
	void update();
	void draw() const;

	/// @brief 生成番号を返す関数
	int32 GetGenerateNum() { return m_generateNum; }


	void UpdateActionState();

	/// @brief 待機アニメーションの更新処理を行う関数
	void UpdateIdleAnimation();

	/// @brief 攻撃アニメーションを実行する関数
	void ExecuteAttackAnimation();

	/// @brief 被ダメージアニメーションを実行する関数
	void ExecuteReceiveDamageAnimation();

	/// @brief 死亡アニメーションをする実行する関数
	void ExecuteDeadAnimation();

	/// @brief アクションステートを設定する関数 
	void SetActionState(const int32 actionNum)
	{
		switch (actionNum)
		{
		case ActionState::Idle:
			m_actionState = ActionState::Idle;
			break;
		case ActionState::Attack:
			m_actionState = ActionState::Attack;
			break;
		case ActionState::ReceiveDamage:
			m_actionState = ActionState::ReceiveDamage;
			break;
		case ActionState::Die:
			m_actionState = ActionState::Die;
			break;
		}
	}

	/// HP ///

	/// @brief 死亡処理を行う関数
	void DeathProcess();

	bool GetIsDead() const { return m_isDead; }

	/// @brief エネミーのHpを返す関数
	int32 GetEnemyHp() const{ return m_currentHp; }
	/// @brief エネミーのhpを設定する関数
	void SetEnemyHp(int32 hp) { m_currentHp = hp; }

	/// ATK ///
	
	/// @brief 敵の攻撃力を返す関数
	int32 GetEnemyAtk() const{ return m_currentAtk; }

	/// @brief エネミーのHpの割合を計算する関数
	/// @details (詳)PctはPercentageの略です 
	int32 CalculatePctOfHp()
	{
		return m_enemyHealthPct = m_fullHealthPct * (m_currentHp / m_maxHp);
	}

private:

	///　描画変数 ///
#pragma region Draw

	String m_assetName;  // アセット名

	const int32 m_maxAnimationFrame{ 25 }; // アニメーションフレームの最大値
	
	const int32 m_maxAnimationNum{ 6 };    // アニメーションの最大枚数

	const int32 m_maxAttackAnimationNum{ 5 }; // 攻撃アニメーションの最大枚数

	const int32 m_maxDamageAnimationNum{ 3 }; // 被ダメージアニメーションの最大枚数

	const int32 m_maxDeadAnimationNum{ 3 }; // 死亡アニメーションの最大枚数

	Vec2 m_enemyPos{ 1150.0, 600.0 };  // エネミーの座標

	Rect m_regionAtEnemy{ 0, 0, 200, 200 };// 画像取得範囲

	int32 m_animationFrameCount{ 0 };   // アニメーションフレームのカウンター
	
	int32 m_animationNumX{ 0 };  // X軸のアニメーション枚数

	int32 m_animationNumY{ 0 };  // Y軸のアニメーション枚数
#pragma endregion

	/// ステータス変数 ///
#pragma region status

	LifeState m_lifeState; // 生死の状態

	ActionState m_actionState; // 行動の状態

	int32 m_generateNum; // 生成番号

	const int32 m_fullHealthPct{ 100 };        // 体力の最大割合

	int32 m_enemyHealthPct{ m_fullHealthPct };  // プレイヤーの割合

	double m_maxHp;                           // 最大体力：体力の割合を計算するためdouble型

	int32 m_currentHp;                       // 現在の体力

	int32 m_currentAtk;                      // 現在の攻撃力

	EnemyData m_masterData; // 敵の仕様（名前や最大HP、攻撃力など）

	bool m_isAttacked{ false }; // 攻撃したかどうかのフラグ

	bool m_isReceivedDamage{ false }; // ダメージを受けたかどうかのフラグ

	bool m_isDead{ false };  // 死亡フラグ
#pragma endregion
	
};
