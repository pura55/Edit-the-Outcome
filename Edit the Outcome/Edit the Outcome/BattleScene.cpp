#include "stdafx.h"
#include "BattleScene.hpp"

BattleScene::BattleScene(const InitData& init):ProjectApp::Scene{ init }
{
	// バトルシーンのアセットを読み込み
	//getData().globalData.imageLoader.LoadBattleAssets();

	// プレイヤーの生成
	GeneratePlayer();

	// エネミーの生成
	GenerateEnemies();

	// 参照を必要とするクラスに参照を渡す
	PassReferences();

	// コマンドマスターデータの参照を渡す
	// 現在は使う予定はないが一度コメントアウトする
	//commandManager.SetData(getData().globalData.m_commandMasterTable);

	// コマンドの進捗データの参照を渡す
	m_commandManager.SetData(getData().globalData.m_commandProgress);
}

void BattleScene::update()
{
	//シーン上部でスクリプトを更新
	RunSystems();

	if (m_battleSystem.GetBattleEnd())
	{
		// 敗北時はタイトルシーンへ遷移
		if (m_battleSystem.GetIsLose())
		{
			// ラウンドをリセット
			getData().globalData.ResetRound();

			changeScene(State::GameOverScene);
		}
		// 勝利時はバトルシーンへ遷移
		if (m_battleSystem.GetIsWin())
		{
			// 一定ラウンドを進んでいたらクリアシーンへ遷移
			if (7 <= getData().globalData.m_currentRound)
			{
				changeScene(State::ClearScene);
				return;
			}

			// ラウンドを進める
			getData().globalData.AddRound();

			changeScene(State::CutScene);
			return;
		}
	}

	// デバッグ用コード
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
	m_battleSystem.update(m_commandManager, m_enemyActionManager, m_battleUI);

	// バトルBgレンダラーを更新
	m_battleBgRenderer.update();
	m_battleBgRenderer.draw();

	// プレイヤーを更新
	m_player->update();
	m_player->draw();

	// エネミーを更新;
	for (auto& enemy : m_activeEnemies)
	{
		enemy->update();
		enemy->draw();
	}

	//バトルUIを更新
	m_battleUI.update();
	m_battleUI.draw();
}

void BattleScene::GeneratePlayer()
{
	// std::moveでスポナーからシーンにエネミーの所有権を譲渡
	m_player = std::move(m_spawner.GeneratePlayer(getData().globalData.m_currentCharacterID,
		                  getData().globalData.m_playerProgress));
}

void BattleScene::GenerateEnemies()
{
	// std::moveでスポナーからシーンにエネミーの所有権を譲渡
	m_activeEnemies = std::move(m_spawner.GenerateEnemies(getData().globalData.m_currentRound, getData().globalData, getData().globalData.m_randomEngine));
}

void BattleScene::PassReferences()
{
	if (m_player && !m_activeEnemies.empty()) // 中身が確実に生成されているかチェック
	{
		// 参照関係を構築
		m_battleSystem.SetReference(*m_player, m_activeEnemies);
		m_battleUI.SetReference(m_battleSystem, m_commandManager, m_targetSelectSystem, *m_player, m_activeEnemies);
		m_healthManager.SetReference(*m_player, m_activeEnemies, m_battleUI);
		m_commandManager.SetReference(m_targetSelectSystem, m_healthManager, *m_player);
		m_targetSelectSystem.SetReference(*m_player, m_activeEnemies);
		m_enemyActionManager.SetReference(m_healthManager, m_activeEnemies);
	}
	else
	{
		throw Error{ U"プレイヤーもしくはエネミーの生成されていません！初期化漏れの可能性があります。"};
	}
}
