#pragma once
#include "Common.hpp"
#include "BattleSystem.hpp"
#include "BattleBgRenderer.hpp"
#include "BattleUI.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class BattleScene : public ProjectApp::Scene
{
public:
	BattleScene(const InitData& init);
	void update() override;
	void draw() const override;

	/// @brief バトルシーン内のスクリプトのupdate()とdraw()を更新する関数
	void RunSystems();

private:
	//バトルシステムを保持
	BattleSystem battleSystem;
	//バトルシーンBgレンダラーを保持
	BattleBgRenderer battleBgRenderer;
	//バトルUIを保持
	BattleUI battleUI;

	//プレイヤーを保持
	// スマートポインタを使用しエラーを防止
	std::unique_ptr<Player> m_player;

	//エネミーを保持
	std::vector<Enemy> m_activeEnemies;
};
