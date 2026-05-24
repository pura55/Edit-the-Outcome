#include "stdafx.h"
#include "BattleScene.hpp"



BattleScene::BattleScene(const InitData& init):ProjectApp::Scene{ init }
{
}

void BattleScene::update()
{
	//update
	battleSystem.update();
	battleSystem.draw();
	battleUI.update();
	battleUI.draw();

	if (battleSystem.GetBattleEnd())
	{
		//タイトルシーンへ遷移
		changeScene(State::TitleScene);
	}
	if (KeyEscape.down())
	{
		//ゲームを終了
		System::Exit();
	}
}

void BattleScene::draw() const
{
}
