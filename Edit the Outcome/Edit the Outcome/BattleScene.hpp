#pragma once
#include "Common.hpp"
#include "BattleSystem.hpp"
#include "BattleBgRenderer.hpp"
#include "CharacterRenderer.hpp"
#include "BattleUI.hpp"

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
	//キャラクターレンダラーを保持
	CharacterRenderer characterRenderer;
	//バトルUIを保持
	BattleUI battleUI;
};
