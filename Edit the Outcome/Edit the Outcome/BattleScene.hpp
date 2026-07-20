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
	// バトルシステムを保持
	BattleSystem battleSystem;
	// バトルシーンBgレンダラーを保持
	BattleBgRenderer battleBgRenderer;
	// バトルUIを保持
	BattleUI battleUI;
	// ヘルスマネージャーを保持
	HealthManager healthManager;
	// コマンドマネージャーを保持
	CommandManager commandManager;
	// ターゲットセレクトシステムを保持
	TargetSelectSystem targetSelectSystem;
	// エネミーアクションマネージャーを保持
	EnemyActionManager enemyActionManager;

	// プレイヤーを保持
	// スマートポインタを使用しエラーを防止
	std::unique_ptr<Player> m_player;

	// エネミーを保持
	std::vector<Enemy> m_activeEnemies;
};
