#pragma once
#include "Common.hpp"

class BattleScene : public ProjectApp::Scene
{
public:
	BattleScene(const InitData& init);
	void update() override;
	void draw() const override;

private:

};
