#include "BattleSystem.h"

BattleSystem::BattleSystem()
{
	state = BattleState::Init;
	currentStateText = "Init";
	isBattleEnd = false;
}

BattleSystem::~BattleSystem()
{
}

void BattleSystem::Update()
{
	switch (state)
	{
	case BattleState::Init:
		Init();
		break;
	
	case BattleState::Start:
		if (Start())
			state = BattleState::PlayerInput;
		break;
	case BattleState::PlayerInput:
		//プレイヤーが入力を終えたら、EnemyActionに移行する
		//未確定の場合は留まる
		if (PlayerInput())
			state = BattleState::EnemyAction;
		break;
		
	case BattleState::EnemyAction:
		//敵の行動が終わったら、TurnEndに移行する
		//未確定の場合は留まる
		if (EnemyAction())
			state = BattleState::TurnEnd;
		break;

	case BattleState::TurnEnd:
		//ターン終了の処理が終わったら、PlayerInputに移行する
		//バトルを終了する場合は、BattleEndに移行する
		TurnEnd();
		if (CheckHitKey(KEY_INPUT_4))
		{
			state = BattleState::PlayerInput;
		}
		if (CheckHitKey(KEY_INPUT_5))
		{
			state = BattleState::BattleEnd;
		}
		break;

	case BattleState::BattleEnd:
		BattleEnd();
		break;
	}
}

void BattleSystem::Draw()
{
	DrawString(200, 200, currentStateText.c_str(), GetColor(255,255,255));
}

void BattleSystem::Init()
{
	state = BattleState::Start;
}

bool BattleSystem::Start()
{
	currentStateText = "Start";
	if (CheckHitKey(KEY_INPUT_1))
	{
	 return true;
	}
	return false;
}

bool BattleSystem::PlayerInput()
{
	currentStateText = "PlayerInput";
	if (CheckHitKey(KEY_INPUT_2))
	{
		return true;
	}
	return false;
}

bool BattleSystem::EnemyAction()
{
	currentStateText = "EnemyAction";
	if (CheckHitKey(KEY_INPUT_3))
	{
		return true;
	}
	return false;
}

 void BattleSystem::TurnEnd()
{
	currentStateText = "TurnEnd";
}

void BattleSystem::BattleEnd()
{
	if (CheckHitKey(KEY_INPUT_T))
	{
		currentStateText = "BattleEnd:now pushing T";
		isBattleEnd = true;
	}
	else
	{
		currentStateText = "BattleEnd";
	}
}
