#pragma once
#include "Common.hpp"
#include "BattleSystem.hpp"
#include "BattleUI.hpp"

class BattleScene : public ProjectApp::Scene
{
public:
	BattleScene(const InitData& init);
	void update() override;
	void draw() const override;

private:
	//バトルシステムを保持
	BattleSystem battleSystem;
	//バトルUIを保持
	BattleUI battleUI;
};
