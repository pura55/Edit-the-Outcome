#pragma once
#include "Common.hpp"
#include "LootSystem.hpp"
#include "LootBg.hpp"
#include "LootUI.hpp"

class LootScene : public ProjectApp::Scene
{
public:
	LootScene(const InitData& init);
	void update() override;
	void RunSystems();

private:
	LootSystem lootSystem;
	LootBg lootBg;
	LootUI lootUI;
};
