#include "BattleScene.h"

BattleScene::BattleScene()
{
	// BattleSystemのインスタンスを探し、見つからなければ新しく作成する
	battleSystem = FindGameObject<BattleSystem>();
	if (!battleSystem)
	{
		battleSystem = new BattleSystem();
	}

	// CommandSystemのインスタンスを探し、見つからなければ新しく作成する
	commandSystem = FindGameObject<CommandSystem>();
	if (!commandSystem)
	{
		commandSystem = new CommandSystem();
	}

	// BattleUIのインスタンスを探し、見つからなければ新しく作成する
	battleUI = FindGameObject<BattleUI>();
	if (!battleUI)
	{
		battleUI = new BattleUI();
	}

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
