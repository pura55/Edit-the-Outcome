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
	// アイテム決定
	DecideKindOfItem();

	// 変数の初期化
	m_selectIndex = 0;
	m_checkIndex = 0;
	m_needAcquireCheck = false;

	// スタック・状態の初期化
	m_menuStack.push(LootMenuState::Select);
	m_lootState = LootState::Selecting;
}

void LootSystem::LootSelecting()
{
	// 確認が必要ない場合、選択処理を行う
	if (not m_needAcquireCheck)
	{
		AcquireItem();
		return;
	}
	else
	{
		// 確認結果が「はい」の場合終了
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
	// A・Dkeyで選択
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

	// Spaceで決定
	if (KeySpace.down())
	{
		m_menuStack.push(LootMenuState::Check);
		m_needAcquireCheck = true;
	}
}

bool LootSystem::CheckAcquisition()
{
	// A・Dkeyで選択
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

	// Spaceで決定
	if (KeySpace.down())
	{
		switch (m_checkIndex)
		{
		case 0: // 「はい」
			m_menuStack.push(LootMenuState::Finish);
			return true;
			break;
		case 1:// 「いいえ」
			m_menuStack.pop(); // メニュースタックをポップ
			m_needAcquireCheck = false;
			m_checkIndex = 0;
			return false;
			break;
		}
	}

	return false;
}
