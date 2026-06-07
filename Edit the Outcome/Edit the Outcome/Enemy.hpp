#pragma once
#include "EnemyData.hpp"

/// <summary>
/// エネミー
/// 
/// エネミーのインスタンスとして生成されるクラス
/// </summary>
class Enemy
{
public:
	Enemy(const EnemyData& masterData);
	void update();
	void draw() const;

	/// @brief プレイヤーアニメーションの更新処理を行う関数
	void AnimationUpdate();

	/// HP ///

	/// @brief エネミーのHpを取得する関数
	int32 GetEnemyHp() { return m_enemyHp; }
	/// @brief エネミーのhpを設定する関数
	void SetEnemyHp(int32 hp) { m_enemyHp = hp; }

private:

	///　描画に関する変数 ///
#pragma region Draw

	// アニメーションカウントの最大値
	const int32 maxAnimationCount{ 20 };

	// アニメーションの最大枚数
	const int32 maxAnimationNum{ 6 };

	// エネミーの座標
	Vec2 m_enemyPos{ 1350.0, 600.0 };

	// 画像取得範囲
	Rect m_regionAtEnemy{ 0, 0, 200, 200 };

	// エネミーのアニメーションカウンター
	int32 enemyAnimationCount{ 0 };

	// プレイヤーのアニメーション枚数
	int32 enemyAnimationNum{ 0 };
#pragma endregion

	EnemyData m_masterData; // 敵の仕様（名前や最大HP、攻撃力など）
	int32 m_currentHp;
	int32 m_currentAtk;
	int32 m_enemyHp{ 5 };  //エネミーのHP
};
