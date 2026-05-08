#include "BattleSystem.h"
#include "CommandSystem.h"

BattleSystem::BattleSystem() : commandSystem(nullptr) //参照をnullptrで初期化
{
	//列挙体の初期化
	state = BattleState::Init;

	//メンバー変数の初期化
	currentStateText = "Init";
	isPlayerInputEnd = false;
	isEnemyActionEnd = false;
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
		StateInit();
		break;
	
	case BattleState::Start:
		if (StateStart())
			state = BattleState::PlayerInput;
		break;

	case BattleState::PlayerInput:
		//プレイヤーが入力を終えたら、EnemyActionに移行する
		//未確定の場合は留まる
		StatePlayerInput();
		break;
		
	case BattleState::EnemyAction:
		//敵の行動が終わったら、TurnEndに移行する
		//未確定の場合は留まる
		if (StateEnemyAction())
			state = BattleState::TurnEnd;
		break;

	case BattleState::TurnEnd:
		//ターン終了の処理が終わったら、PlayerInputに移行する
		//バトルを終了する場合は、BattleEndに移行する
		StateTurnEnd();
		break;

	case BattleState::BattleEnd:
		StateBattleEnd();
		break;
	}
}

void BattleSystem::Draw()
{
	DrawString(200, 200, currentStateText.c_str(), GetColor(255,255,255));
}

void BattleSystem::SetReference()
{
	//CommandSystemの参照を取得
	commandSystem = FindGameObject<CommandSystem>();
}

void BattleSystem::StateInit()
{
	state = BattleState::Start;
}

bool BattleSystem::StateStart()
{
	currentStateText = "Start";
	if (CheckHitKey(KEY_INPUT_1))
	{
		commandSystem->SetStateActive();
		return true;
	}
	return false;
}

void BattleSystem::StatePlayerInput()
{
	currentStateText = "PlayerInput";
	if(commandSystem->GetIsStateIdle())
	{ 
		commandSystem->SetStateActive();
	}
	if (isPlayerInputEnd)
	{
		state = BattleState::EnemyAction;
	}
}

bool BattleSystem::StateEnemyAction()
{
	currentStateText = "EnemyAction";
	if (CheckHitKey(KEY_INPUT_3))
	{
		return true;
	}
	return false;
}

 void BattleSystem::StateTurnEnd()
{
	currentStateText = "TurnEnd";
	if (CheckHitKey(KEY_INPUT_4))
	{
		SetPlayerInputEnd(false);
		state = BattleState::PlayerInput;
		commandSystem->ResetCommand();
	}
	if (CheckHitKey(KEY_INPUT_5))
	{
		state = BattleState::BattleEnd;
	}
}

void BattleSystem::StateBattleEnd()
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

