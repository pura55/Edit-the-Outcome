#include "stdafx.h"
#include "BattleScene.hpp"



BattleScene::BattleScene(const InitData& init):ProjectApp::Scene{ init }
{
	//バトルシーンのアセットを読み込み
	getData().globalData.imageLoader.LoadBattleAssets();
	//参照を渡す
	battleUI.SetReference(battleSystem, getData().globalData.imageLoader);
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
