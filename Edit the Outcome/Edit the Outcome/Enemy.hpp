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
	Enemy(const EnemyData& masterData, int32 generate);
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

	// アセット名
	String m_assetName;

	// アニメーションカウントの最大値
	const int32 m_maxAnimationCount{ 25 };

	// アニメーションの最大枚数
	const int32 m_maxAnimationNum{ 6 };

	// 生成番号
	int32 m_generateNum;

	// エネミーの座標
	Vec2 m_enemyPos{ 1150.0, 600.0 };

	// 画像取得範囲
	Rect m_regionAtEnemy{ 0, 0, 200, 200 };

	// エネミーのアニメーションカウンター
	int32 m_enemyAnimationCount{ 0 };

	// プレイヤーのアニメーション枚数
	int32 m_enemyAnimationNum{ 0 };
#pragma endregion

	EnemyData m_masterData; // 敵の仕様（名前や最大HP、攻撃力など）
	int32 m_currentHp;
	int32 m_currentAtk;
	int32 m_enemyHp{ 5 };  //エネミーのHP
};
