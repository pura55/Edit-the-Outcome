#include "BattleScene.h"
#include "BattleSystem.h"
#include "CommandSystem.h"
#include "BattleUI.h"

BattleScene::BattleScene()
{
	battleSystem = new BattleSystem();
	commandSystem = new CommandSystem();
	battleUI = new BattleUI();

	//ŽQÆ‚ÌŽæ“¾
	battleSystem->SetReference();
	commandSystem->SetReference();
	battleUI->SetReference();

	isBattleEnded = false;
}

BattleScene::~BattleScene()
{
}

void BattleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}
	if (battleSystem->GetBattleEnd())
	{
		SceneManager::ChangeScene("TITLE");
	}
}

void BattleScene::Draw()
{
}
