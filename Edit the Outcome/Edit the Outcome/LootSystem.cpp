#include "stdafx.h"
#include "LootSystem.hpp"

LootSystem::LootSystem()
{
}

void LootSystem::update()
{
	if (KeyB.down())
	{
		lootItemSelected = true;
	}
}
