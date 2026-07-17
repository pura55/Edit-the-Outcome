#include "stdafx.h"
#include "BattleScene.hpp"

BattleScene::BattleScene(const InitData& init):ProjectApp::Scene{ init }
{
	//バトルシーンのアセットを読み込み
	getData().globalData.imageLoader.LoadBattleAssets();

	/// プレイヤーの生成 ///
#pragma region GeneratePlayer
	
	int32 currentID = getData().globalData.currentCharacterID; // 現在選ばれているキャラクターのid
	bool isFound = false; // idが見つかったかどうかのフラグ

	// プレイヤーのデータから該当するidを探す
	for (const auto& progress : getData().globalData.m_playerProgress)
	{
		if (progress.id == currentID)
		{
			m_player = std::make_unique<Player>(progress);
			isFound = true;
			break;
		}
	}

	// 見つからない場合の例外処理
	if (not isFound)
	{
		throw Error{ U"GameDataのplayerProgressList内に、ID: {} のプレイヤーデータが存在しません！初期化漏れの可能性があります。"_fmt(currentID) };
	}
#pragma endregion

	/// エネミーの生成 ///
#pragma region GenereteEnemies
	
	int32 numOfTimes = Random<int32>(1, 3); // 生成する回数
	int32 generateCount = 0;                // 生成カウント

	m_activeEnemies.clear(); // エネミーの配列をクリア

	// 生成カウントが回数に達したら生成終了
	while (generateCount != numOfTimes)
	{
		int32 generateId = Random<int32>(1, 2); // 生成するエネミーのid

		// 敵の生成
		//「ID：1スライム」,「ID：２オーク」
		m_activeEnemies.push_back(Enemy(getData().globalData.GetEnemyData(generateId), generateCount));

		generateCount++;
	}
#pragma endregion

	/// ポインタを渡す ///
#pragma region PassPointer
	if (m_player && !m_activeEnemies.empty()) // 中身が確実に生成されているかチェック
	{
		// プレイヤーのポインタを取得
		Player* playerPtr = m_player.get();

		// 必要なサイズのメモリをあらかじめ確保
		std::vector<Enemy*> enemyPtr;
		enemyPtr.reserve(m_activeEnemies.size());

		// アドレスを格納
		for (auto& enemies : m_activeEnemies)
		{
			enemyPtr.push_back(&enemies);
		}

		// ポインタを渡す
		battleSystem.SetReference(playerPtr, enemyPtr);
		battleUI.SetReference(battleSystem, playerPtr,enemyPtr);
		healthManager.SetReference(playerPtr, enemyPtr);
		commandManager.SetReference(targetSelectSystem, healthManager, playerPtr, enemyPtr );
		enemyActionManager.SetReference(healthManager, enemyPtr);
	}
#pragma endregion

	// コマンドマスターデータの参照を渡す
	// 現在は使う予定はないが一度コメントアウトする
	/*commandManager.SetData(getData().globalData.m_commandMasterTable);*/
	// コマンドの進捗データの参照を渡す
	commandManager.SetData(getData().globalData.m_commandProgress);
}

void BattleScene::update()
{
	//シーン上部でスクリプトを更新
	RunSystems();

	if (battleSystem.GetBattleEnd())
	{
		// 敗北時はタイトルシーンへ遷移
		if (battleSystem.GetIsLose())
		{
			changeScene(State::TitleScene);
		}
		// 勝利時はルートシーンへ遷移
		if (battleSystem.GetIsWin())
		{
			changeScene(State::LootScene);
		}
	}

	if (KeyL.down())
	{
		changeScene(State::LootScene);
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
	battleSystem.update(commandManager, enemyActionManager);
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
	battleUI.update(commandManager);
	battleUI.draw(commandManager);
}
