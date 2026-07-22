#pragma once
#include "Common.hpp"
#include "BattleSystem.hpp"
#include "BattleBgRenderer.hpp"
#include "BattleUI.hpp"
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
	BattleSystem battleSystem; // バトルシステムを保持
	
	BattleBgRenderer battleBgRenderer; // バトルシーンBgレンダラーを保持
	
	BattleUI battleUI; // バトルUIを保持

	HealthManager healthManager; // ヘルスマネージャーを保持
	
	CommandManager commandManager; // コマンドマネージャーを保持
	
	TargetSelectSystem targetSelectSystem; // ターゲットセレクトシステムを保持
	
	EnemyActionManager enemyActionManager; // エネミーアクションマネージャーを保持

	// プレイヤーを保持
	// スマートポインタを使用しエラーを防止
	std::unique_ptr<Player> m_player;

	std::vector<Enemy> m_activeEnemies; // エネミーを保持
};
