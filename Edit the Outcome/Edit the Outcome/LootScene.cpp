#include "stdafx.h"
#include "LootScene.hpp"

LootScene::LootScene(const InitData& init) : ProjectApp::Scene{init}
{
	// 参照を必要とするクラスに参照を渡す
	PassReferences();
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

	// デバックコード（コマンドを入力操作で獲得
	if (KeyG.down())
	{
		getData().globalData.m_commandProgress[0].isGet = true;
		getData().globalData.m_commandProgress[1].isGet = true;
		getData().globalData.m_commandProgress[2].isGet = true;
		getData().globalData.m_commandProgress[3].isGet = true;
		getData().globalData.m_commandProgress[4].isGet = true;
		getData().globalData.m_commandProgress[5].isGet = true;
	}
}

void LootScene::RunSystems()
{
	lootSystem.update();

	lootBg.update();
	lootBg.draw();

	lootUI.update();
	lootUI.draw();
}

void LootScene:: PassReferences()
{
	// コマンドのデータ
	std::vector<CommandData>& commandData = getData().globalData.m_commandProgress;

	// プレイヤーのデータ
	std::vector<PlayerProgressData>& playerData = getData().globalData.m_playerProgress;

	// プレイヤーのID
	int32 playerID = getData().globalData.m_currentCharacterID;

	// ルートアイテムに必要なデータをルートシステムに渡す
	lootSystem.SetLootData(commandData, playerData, playerID);

	// ランダムエンジンの参照をルートシステムに渡す
	lootSystem.SetRandomEngine(&getData().globalData.m_randomEngine);

	lootUI.SetReference(lootSystem);
}
