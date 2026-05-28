#include "stdafx.h"
#include "BattleUI.hpp"
#include "BattleSystem.hpp"

BattleUI::BattleUI() :m_battleSystem(nullptr)
{
}

void BattleUI::update()
{
	
	if (!m_battleSystem->GetIsSkillMenu())
	{
		UpdateCursorPos();
	}
	else
	{
		UpdateSubCursorPos();
	}
}

void BattleUI::draw() const
{
	//背景
	TextureAsset(U"BattleBg").drawAt(Scene::Center());

	//コマンドウィンドウ
	{
		TextureAsset(U"CommandWindow").drawAt(m_commandWindowPos);
		Triangle(m_movedFirstPos, m_movedSecondPos, m_movedThirdPos).draw(Palette::White);

		if (m_battleSystem->GetIsSkillMenu())
		{
			TextureAsset(U"SubCommandWindow").drawAt(m_subCommandWindowPos);
			Triangle(m_subMovedFirstPos, m_subMovedSecondPos, m_subMovedThirdPos).draw(Palette::White);
		}
	}

	FontAsset(U"BattleSystem")(U"{}"_fmt(m_currentCommandIndex))
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 300 });
}

void BattleUI::SetReference(BattleSystem& battleSystem, ImageLoader& imageLoader)
{
	m_battleSystem = &battleSystem;
	m_imageLoader = &imageLoader;
}

void BattleUI::UpdateCursorPos()
{
	m_currentCommandIndex = m_battleSystem->GetCommandIndex();
	//commandIndexによってカーソルの座標を移動させる
	m_offsetCursorY = { 32.0 * m_currentCommandIndex };
	m_movedFirstPos = m_cursorFirstPos.movedBy(0, m_offsetCursorY);
	m_movedSecondPos = m_cursorSecondPos.movedBy(0, m_offsetCursorY);
	m_movedThirdPos = m_cursorThirdPos.movedBy(0, m_offsetCursorY);
}

void BattleUI::UpdateSubCursorPos()
{
	m_currentCommandIndex = m_battleSystem->GetCommandIndex();
	//commandIndexによってカーソルの座標を移動させる
	m_subOffsetCursorY = { 32.0 * m_currentCommandIndex };
	m_subMovedFirstPos = m_subCursorFirstPos.movedBy(0, m_subOffsetCursorY);
	m_subMovedSecondPos = m_subCursorSecondPos.movedBy(0, m_subOffsetCursorY);
	m_subMovedThirdPos = m_subCursorThirdPos.movedBy(0, m_subOffsetCursorY);
}

