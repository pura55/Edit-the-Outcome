#include "stdafx.h"
#include "BattleScene.hpp"



BattleScene::BattleScene(const InitData& init):ProjectApp::Scene{ init }
{
	//バトルシーンのアセットを読み込み
	getData().globalData.imageLoader.LoadBattleAssets();


	/// プレイヤーの生成 ///
	// 現在選ばれているキャラクターのid
	int32 currentID = getData().globalData.currentCharacterID;

	bool isFound = false;

	for (const auto& progress : getData().globalData.m_playerProgress)
	{
		if (progress.id == currentID)
		{
			m_player = std::make_unique<Player>(progress);
			isFound = true;
			break;
		}
	}

	if (not isFound)
	{
		throw Error{ U"GameDataのplayerProgressList内に、ID: {} のプレイヤーデータが存在しません！初期化漏れの可能性があります。"_fmt(currentID) };
	}

	/// エネミーの生成 ///
	m_activeEnemies.clear();
	// 「ID：２オーク」
	m_activeEnemies.push_back(Enemy(getData().globalData.GetEnemyData(2)));

	if (m_player) // 中身が確実に生成されているかチェック
	{
		Player* playerPtr = m_player.get();

		// 参照（ポインタ）を安全に渡す
		battleSystem.SetReference(playerPtr);
		battleUI.SetReference(battleSystem, playerPtr);
	}
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
	// バトルシステムを更新
	battleSystem.update();
	battleSystem.draw();

	// バトルBgレンダラーを更新
	battleBgRenderer.update();
	battleBgRenderer.draw();

	// プレイヤーを更新
	m_player->update();
	m_player->draw();

	// エネミーを更新;
	for (auto& enemy : m_activeEnemies)
	{
		enemy.update();
		enemy.draw();
	}

	//バトルUIを更新
	battleUI.update();
	battleUI.draw();
}
