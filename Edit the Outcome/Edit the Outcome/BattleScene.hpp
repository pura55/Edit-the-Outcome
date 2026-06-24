#pragma once
#include "Common.hpp"
#include "BattleSystem.hpp"
#include "BattleBgRenderer.hpp"
#include "BattleUI.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "HealthManager.hpp"
#include "CommandManager.hpp"

class BattleScene : public ProjectApp::Scene
{
public:
	BattleScene(const InitData& init);
	void update() override;
	void draw() const override;

	/// @brief バトルシーン内のスクリプトのupdate()とdraw()を更新する関数
	void RunSystems();

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

	// プレイヤーを保持
	// スマートポインタを使用しエラーを防止
	std::unique_ptr<Player> m_player;

	// エネミーを保持
	std::vector<Enemy> m_activeEnemies;
};
