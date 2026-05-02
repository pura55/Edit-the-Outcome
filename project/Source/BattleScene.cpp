#include "BattleScene.h"

BattleScene::BattleScene()
{
	battleSystem = new BattleSystem();
	isBattleEnded = false;
}

BattleScene::~BattleScene()
{
}

void BattleScene::Update()
{
	if (battleSystem->GetBattleEnd())
	{
		SceneManager::ChangeScene("TITLE");
	}
}

void BattleScene::Draw()
{
}
