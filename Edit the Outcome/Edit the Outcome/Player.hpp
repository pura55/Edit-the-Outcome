#pragma once
#include "PlayerProgressData.hpp"

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

	/// @brief プレイヤーアニメーションの更新処理を行う関数
	void AnimationUpdate();

	Vec2 GetPlayerPos()const { return m_playerPos; }

	/// HP関数 ///
#pragma region HP

	/// @brief 現在のプレイヤーのHpを取得する関数
	int32 GetCurrentPlayerHp()const { return m_currentHp; }

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

#pragma endregion
    
private:

	/// 描画変数 ///
#pragma region draw

	const int32 m_maxAnimationCount{ 25 };   // アニメーションカウントの最大値

	const int32 m_maxAnimationNum{ 6 };      // アニメーションの最大枚数

	Vec2 m_playerPos{ 550.0, 600.0 };        // プレイヤーの座標

	Rect m_regionAtPlayer{ 0, 0, 200, 200 }; // 画像取得範囲

	int32 m_playerAnimationCount{ 0 };       // プレイヤーのアニメーションカウンター

	int32 m_playerAnimationNum{ 0 };         // プレイヤーのアニメーション枚数
#pragma endregion

	/// ステータス変数 ///
#pragma region status
	
	const int32 fullHealthPct{ 100 };        // 体力の最大割合
	
	int32 playerHealthPct{ fullHealthPct };  // プレイヤーの割合

	double m_maxHp;                           // 最大体力：体力の割合を計算するためdouble型

	int32 m_currentHp;                       // 現在の体力

	int32 m_currentAtk;                      // 現在の攻撃力

	PlayerProgressData m_progress;   // プレイヤーのデータ保持
#pragma endregion


};

	
	
