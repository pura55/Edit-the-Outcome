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

	/// HP ///
	/// @brief 現在のプレイヤーのHpを取得する関数
	int32 GetCurrentPlayerHp() { return m_currentHp; }
	/// @brief プレイヤーのHpを取得する関数
	int32 GetPlayerHp() { return m_playerHp; }
	/// @brief プレイヤーのhpを設定する関数
	void SetPlayerHp(int32 hp) { m_playerHp = hp; }

	/// ATK ///
	
	/// @brief プレイヤーのAtkを取得す関数
	int32 GetPlayerAtk() { return m_playerAtk; }
	/// @brief プレイヤーのAtkを設定する関数
	void SetPlayerAtk(int32 atk) { m_playerAtk = atk; }
    
private:

	/// 描画に関する変数 ///
#pragma region draw

	// アニメーションカウントの最大値
	const int32 maxAnimationCount{ 20 };

	// アニメーションの最大枚数
	const int32 maxAnimationNum{ 6 };

	// プレイヤーの座標
	Vec2 m_playerPos{ 450.0, 600.0 };

	// 画像取得範囲
	Rect m_regionAtPlayer{ 0, 0, 200, 200 };

	// プレイヤーのアニメーションカウンター
	int32 playerAnimationCount{ 0 };

	// プレイヤーのアニメーション枚数
	int32 playerAnimationNum{ 0 };
#pragma endregion

	PlayerProgressData m_progress;
	int32 m_currentHp;
	int32 m_currentAtk;
	int32 m_playerHp{10};  //プレイヤーのHP
	int32 m_playerAtk{1};  //プレイヤーの攻撃力
};
