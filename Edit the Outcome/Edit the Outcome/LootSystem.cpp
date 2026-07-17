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
		LootInit();
		break;
	case LootState::Selecting:
		LootSelecting();
		break;
	case LootState::Finished:
		LootFinished();
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

void LootSystem::LootInit()
{
	DecideKindOfItem();

	m_selectIndex = 0;
	m_checkIndex = 0;
	m_needAcquireCheck = false;
}

void LootSystem::LootSelecting()
{
	if (not m_needAcquireCheck)
	{
		AcquireItem();
	}
	else
	{
		if (CheckAcquisition())
		{
			m_lootState = LootState::Finished;
			return;
		}
	}
}

void LootSystem::LootFinished()
{
}

void LootSystem::DecideKindOfItem()
{

}

void LootSystem::AcquireItem()
{
	if (KeyA.down())
	{
		m_selectIndex -= 1;

		if (m_selectIndex < 0)
		{
			m_selectIndex = 0;
		}
	}

	if (KeyD.down())
	{
		m_selectIndex += 1;

		if (m_selectIndex >= m_maxSelectIndex)
		{
			m_selectIndex = m_maxSelectIndex;
		}
	}

	if (KeySpace.down())
	{
		m_needAcquireCheck = true;
	}
}

bool LootSystem::CheckAcquisition()
{
	if (KeyA.down())
	{
		m_checkIndex -= 1;

		if (m_checkIndex < 0)
		{
			m_checkIndex = 0;
		}
	}

	if (KeyD.down())
	{
		m_checkIndex += 1;

		if (m_checkIndex >= m_maxCheckIndex)
		{
			m_checkIndex = m_maxCheckIndex;
		}
	}

	if (KeySpace.down())
	{
		switch (m_checkIndex)
		{
		case 0:
			return true;
			break;
		case 1:
			m_needAcquireCheck = false;
			return false;
			break;
		}
	}

	return false;
}
