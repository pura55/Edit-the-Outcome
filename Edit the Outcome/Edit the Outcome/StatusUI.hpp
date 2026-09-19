#pragma once
#include <Siv3D.hpp>

// 前方宣言
class Player;
class Enemy;

/// <summary>
/// ステータスUI
///
/// ステータスのUIクラス
/// </summary>
class StatusUI
{
public:
	StatusUI();
	void update();
	void draw(Player* player, const std::vector<Enemy*>& enemies) const;

private:
	Vec2 m_screenSize{ 140.0, 25.0 };
	// ステータスの座標（hpなど）
	const double m_statusPosY{ 450.0 };
};
