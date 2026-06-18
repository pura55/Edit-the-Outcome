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

	/// @brief 生成番号を返す関数
	int32 GetGenerateNum() { return m_generateNum; }


	/// @brief エネミーアニメーションの更新処理を行う関数
	void AnimationUpdate();

	/// HP ///

	/// @brief エネミーのHpを取得する関数
	int32 GetEnemyHp() { return m_currentHp; }
	/// @brief エネミーのhpを設定する関数
	void SetEnemyHp(int32 hp) { m_currentHp = hp; }

	/// @brief エネミーのHpの割合を計算する関数
	/// @details (詳)PctはPercentageの略です 
	int32 CalculatePctOfHp()
	{
		return enemyHealthPct = fullHealthPct * (m_currentHp / m_maxHp);
	}

private:

	///　描画変数 ///
#pragma region Draw

	String m_assetName;  // アセット名

	const int32 m_maxAnimationCount{ 25 }; // アニメーションカウントの最大値
	
	const int32 m_maxAnimationNum{ 6 };    // アニメーションの最大枚数
	
	Vec2 m_enemyPos{ 1150.0, 600.0 };  // エネミーの座標

	Rect m_regionAtEnemy{ 0, 0, 200, 200 };// 画像取得範囲

	int32 m_enemyAnimationCount{ 0 };   // エネミーのアニメーションカウンター
	
	int32 m_enemyAnimationNum{ 0 };  // プレイヤーのアニメーション枚数
#pragma endregion

	/// ステータス変数 ///
#pragma region status

	int32 m_generateNum; // 生成番号

	const int32 fullHealthPct{ 100 };        // 体力の最大割合

	int32 enemyHealthPct{ fullHealthPct };  // プレイヤーの割合

	double m_maxHp;                           // 最大体力：体力の割合を計算するためdouble型

	int32 m_currentHp;                       // 現在の体力

	int32 m_currentAtk;                      // 現在の攻撃力

	EnemyData m_masterData; // 敵の仕様（名前や最大HP、攻撃力など）
#pragma endregion
	
};
