#pragma once
#include "Common.hpp"
#include "LootSystem.hpp"

class LootScene : public ProjectApp::Scene
{
public:
	LootScene(const InitData& init);
	void update() override;
	void RunSystems();

private:
	LootSystem lootSystem;
};
