#pragma once
#include <Siv3D.hpp>

class LootUI
{
public:
	LootUI();
	void update();
	void draw() const;

private:
	Vec2 m_dwarfPos{ 200.0, 600.0 };
	Vec2 m_speechFramePos{ 225.0, 550.0 };
	Vec2 m_framePos{ 330.0, 350.0 };
};
