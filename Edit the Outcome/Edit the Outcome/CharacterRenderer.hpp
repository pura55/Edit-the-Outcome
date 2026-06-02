#pragma once
#include <Siv3D.hpp>

/// <summary>
/// キャラクターレンダラー
/// 
/// バトルで各キャラクターを表示するクラス
/// </summary>
class CharacterRenderer
{
public:
	CharacterRenderer();
	void update();
	void draw() const;

private:

	/// プレイヤー ///

#pragma region Player
	//プレイヤーの座標
	Vec2 m_playerPos{ 350.0, 500.0 };

	//画像取得範囲
	Rect m_playerAtRegion{ 0, 0, 200, 200 };
#pragma endregion

	///　エネミー ///

#pragma region Enemy
	Vec2 m_enemyPos{ 600.0, 200.0 };
#pragma endregion
};
