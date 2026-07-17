#include "stdafx.h"
#include "LootSystem.hpp"

LootSystem::LootSystem()
{
}

void LootSystem::update()
{
	switch (m_lootState)
	{
	case LootState::Init:
		break;
	case LootState::Selecting:
		break;
	case LootState::Finished:
		break;
	}

	if (KeyB.down())
	{
		m_lootItemSelected = true;
	}
}

void LootSystem::SetLootData(std::vector<CommandData>& commandData, std::vector<PlayerProgressData>& playerData)
{
	// データの参照を格納
	m_commandData = commandData;
	m_playerData = playerData;
}
