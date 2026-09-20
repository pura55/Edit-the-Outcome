#pragma once
#include "Common.hpp"
#include "BattleSystem.hpp"
#include "BattleBgRenderer.hpp"
#include "BattleUI.hpp"
#include "Spawner.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "HealthManager.hpp"
#include "CommandManager.hpp"
#include "TargetSelectSystem.hpp"
#include "EnemyActionManager.hpp"

/// <summary>
/// バトルシーン
/// </summary>
class BattleScene : public ProjectApp::Scene
{
public:
	BattleScene(const InitData& init);
	void update() override;
	void draw() const override;

	/// @brief バトルシーン内のスクリプトのupdate()とdraw()を更新する関数
	void RunSystems();

	/// @brief プレイヤーを生成する関数
	void GeneratePlayer();

	/// @brief エネミーを生成する関数
	void GenerateEnemies();

	/// @brief 参照を必要必要としているクラスに参照を渡す関数
	void PassReferences();

private:
	BattleSystem m_battleSystem; // バトルシステムを保持
	
	BattleBgRenderer m_battleBgRenderer; // バトルシーンBgレンダラーを保持
	
	BattleUI m_battleUI; // バトルUIを保持

	HealthManager m_healthManager; // ヘルスマネージャーを保持
	
	CommandManager m_commandManager; // コマンドマネージャーを保持
	
	TargetSelectSystem m_targetSelectSystem; // ターゲットセレクトシステムを保持
	
	EnemyActionManager m_enemyActionManager; // エネミーアクションマネージャーを保持

	Spawner m_spawner; // スポナーを保持

	// プレイヤーを保持
	// スマートポインタを使用しエラーを防止
	std::unique_ptr<Player> m_player;

	std::vector<std::unique_ptr<Enemy>> m_activeEnemies; // エネミーを保持
};
