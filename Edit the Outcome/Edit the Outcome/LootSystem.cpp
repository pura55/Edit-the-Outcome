#include "stdafx.h"
#include "LootSystem.hpp"

LootSystem::LootSystem():m_randomEngine(nullptr)
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

void LootSystem::SetLootData(std::vector<CommandData>& commandData, std::vector<PlayerProgressData>& playerData, int32 playerID)
{
	// データの参照を格納
	m_commandData = commandData;
	m_playerData = playerData;

	// IDの格納
	m_currentPlayerID = playerID;
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
	// ルートアイテムのデータのサイズを設定
	m_lootItemData.resize(m_itemDataSize);

	int32 registItemCount = 0; // 登録アイテムのカウント

	// 登録カウントがルートアイテムのサイズ未満の場合実行
	while (registItemCount < m_itemDataSize)
	{
		// アイテムの確率を格納
		double rateOfItem = m_randomEngine->RandomDouble(ItemRate::MIN, ItemRate::MAX);

		
		if (rateOfItem < ItemRate::COMMAND_APPEARING)
		{
			// コマンドが出現する場合
			double rateOfCommand = m_randomEngine->RandomDouble(ItemRate::MIN, ItemRate::MAX);

			if (rateOfCommand < ItemRate::COMMAND_AVG)
			{

			}
			else if (rateOfCommand < ItemRate::COMMAND_AVG * 2)
			{

			}
			else if (rateOfCommand < ItemRate::COMMAND_AVG * 3)
			{

			}
			else if (rateOfCommand < ItemRate::COMMAND_AVG * 4)
			{

			}
			else if (rateOfCommand < ItemRate::COMMAND_AVG * 5)
			{

			}
			
		}
		else
		{
			// ステータスが出現する場合

		}
	}
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
