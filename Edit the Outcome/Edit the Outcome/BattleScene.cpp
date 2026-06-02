#include "stdafx.h"
#include "BattleScene.hpp"



BattleScene::BattleScene(const InitData& init):ProjectApp::Scene{ init }
{
	//バトルシーンのアセットを読み込み
	getData().globalData.imageLoader.LoadBattleAssets();
	//参照を渡す
	battleSystem.SetReference(getData().globalData.player, getData().globalData.enemy);
	//参照を渡す
	battleUI.SetReference(battleSystem);
}

void BattleScene::update()
{
	//シーン上部でスクリプトを更新
	RunSystems();

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

void BattleScene::RunSystems()
{
	//バトルシステムを更新
	battleSystem.update();
	battleSystem.draw();

	//バトルBgレンダラーを更新
	battleBgRenderer.update();
	battleBgRenderer.draw();

	//キャラクターレンダラーを更新
	characterRenderer.update();
	characterRenderer.draw();

	//バトルUIを更新
	battleUI.update();
	battleUI.draw();
}
