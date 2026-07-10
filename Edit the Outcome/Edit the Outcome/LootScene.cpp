#include "stdafx.h"
#include "LootScene.hpp"

LootScene::LootScene(const InitData& init) : ProjectApp::Scene{init}
{
}

void LootScene::update()
{
	//シーン上部でスクリプトを更新
	RunSystems();

	// ルートアイテムの選択が終了したらバトルシーンへ遷移
	if (lootSystem.GetLootItemSelected())
	{
		changeScene(State::BattleScene);
	}
}

void LootScene::RunSystems()
{
	lootSystem.update();
}
