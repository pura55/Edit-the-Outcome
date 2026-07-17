#include "stdafx.h"
#include "LootUI.hpp"

LootUI::LootUI()
{
}

void LootUI::update()
{
}

void LootUI::draw() const
{
	TextureAsset(U"DwarfKind").drawAt(m_dwarfPos);
	TextureAsset(U"SpeechFrame").drawAt(m_speechFramePos);

	for (int32 i = 0; i < 3; i++)
	{
		TextureAsset(U"LootFrame").drawAt(m_framePos.x + i*320, m_framePos.y);
	}
}
