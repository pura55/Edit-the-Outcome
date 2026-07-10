#pragma once
#include <Siv3D.hpp>

class LootSystem
{
public:
	LootSystem();
	void update();

	bool GetLootItemSelected() { return lootItemSelected; }

private:
	bool lootItemSelected{ false };
};
