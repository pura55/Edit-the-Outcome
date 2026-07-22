#pragma once
#include "Common.hpp"
#include "LootSystem.hpp"
#include "LootBg.hpp"
#include "LootUI.hpp"

class LootScene : public ProjectApp::Scene
{
public:
	LootScene(const InitData& init);
	void update() override;

	/// @brief ルートシーン内のスクリプトのupdate()とdraw()を更新する関数
	void RunSystems();

	/// @brief 参照を必要必要としているクラスに参照を渡す関数
	void PassReferences();

private:
	LootSystem lootSystem; // ルートシステムの保持

	LootBg lootBg; // ルートBgの保持

	LootUI lootUI; // ルートUIの保持
};
