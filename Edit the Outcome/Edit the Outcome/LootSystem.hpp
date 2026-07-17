#pragma once
#include <Siv3D.hpp>
#include "CommandData.hpp"
#include "PlayerProgressData.hpp"

enum LootState
{
	Init,
	Selecting,
	Finished
};

class LootSystem
{
public:
	LootSystem();
	void update();

	// ルートに関わるデータを格納する関数
	void SetLootData(std::vector<CommandData>& commandData, std::vector<PlayerProgressData>& playerData);

	// ルートアイテムを選択したかどうかのフラグを返す関数
	bool GetLootItemSelected() { return m_lootItemSelected; }

private:
	LootState m_lootState;

	bool m_lootItemSelected{ false };

	std::vector<CommandData> m_commandData;

	std::vector<PlayerProgressData> m_playerData;
};
