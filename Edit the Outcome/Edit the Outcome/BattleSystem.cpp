#include "stdafx.h"
#include "BattleSystem.hpp"

BattleSystem::BattleSystem()
{
}

void BattleSystem::update()
{
	switch (state)
	{
	case BattleState::Init:
		StateInit();
		break;

	case BattleState::Start:
		if (StateStart())
			state = BattleState::CommandInput;
		break;

	case BattleState::CommandInput:
		//プレイヤーが入力を終えたら、EnemyActionに移行する
		//未確定の場合は留まる
		StateCommandInput();
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

void BattleSystem::draw() const
{
	FontAsset(U"BattleSystem")(currentStateText)
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });
}

void BattleSystem::StateInit()
{
	state = BattleState::Start;
	menuStack.push(MenuState::Base);
}

bool BattleSystem::StateStart()
{
	currentStateText = U"Start";
	if (Key1.down())
	{
		return true;
	}
	return false;
}

void BattleSystem::StateCommandInput()
{
	currentStateText = U"CommandInput";

	if (menuStack.top() == MenuState::Base)//ベースメニュー時
	{
		//コマンド操作
		SelectCommandIndex();
		//	現在のコマンドインデックス
		switch (currentCommandIndex)
		{
		case 0: //攻撃
			type = CommandType::Attack;
			break;

		case 1: //防御
			type = CommandType::Diffence;
			break;

		case 2: //スキル
			type = CommandType::Skills;
			break;
		}

		switch (type)
		{
		case CommandType::Attack: //攻撃選択時
			if (KeySpace.down())
			{
				state = BattleState::EnemyAction;
			}
			break;
		case CommandType::Diffence: //防御を選択時
			if (KeySpace.down())
			{
				state = BattleState::EnemyAction;
			}
			break;
		case CommandType::Skills: //スキルを選択時
			if (KeySpace.down())
			{
				//スキルのメニューへ移る
				menuStack.push(MenuState::Skill);
			}
			break;
		}
	}
	else if (menuStack.top() == MenuState::Skill) //スキルメニュー時
	{
		//コマンド操作
		SelectCommandIndex();
		if (KeySpace.down())
		{
			state = BattleState::EnemyAction;
		}
		if (KeyB.down())
		{
			//ベースのメニューへ戻る
			menuStack.pop();
		}
		else if (menuStack.top() == MenuState::Skill)
		{
			if (KeySpace.down())
			{
				state = BattleState::EnemyAction;
			}
			if (KeyB.down())
			{
				menuStack.push(MenuState::Base);
			}
		}
	}

}

bool BattleSystem::StateEnemyAction()
{
	currentStateText = U"EnemyAction";
	if (Key3.down())
	{
		return true;
	}
	return false;
}

void BattleSystem::StateTurnEnd()
{
	currentStateText = U"TurnEnd";
	if (Key4.down())
	{
		SetPlayerInputEnd(false);
		state = BattleState::CommandInput;
	}
	if (Key5.down())
	{
		state = BattleState::BattleEnd;
	}
}

void BattleSystem::StateBattleEnd()
{
	if (KeyT.down())
	{
		currentStateText = U"BattleEnd:now pushing T";
		isBattleEnd = true;
	}
	else
	{
		currentStateText = U"BattleEnd";
	}
}

void BattleSystem::SelectCommandIndex()
{
	//コマンドメニュー内のコマンド数を設定
	if (menuStack.top() == MenuState::Base)
	{
		MaxCommandIndex = 3;
	}
	else
	{
		MaxCommandIndex = 1;
	}

	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyW.down())
	{
		//コマンドのインデックスを減らす
		currentCommandIndex -= 1;

		//コマンドのインデックスが0未満にならないようにする
		if (currentCommandIndex < MaxCommandIndex-1)
		{
			currentCommandIndex = MaxCommandIndex;
		}
	}
	if (KeyS.down())
	{
		//コマンドのインデックスを増やす
		currentCommandIndex += 1;

		//コマンドのインデックスが2より大きくならないようにする
		if (currentCommandIndex > MaxCommandIndex-1)
		{
			currentCommandIndex = MaxCommandIndex;
		}
	}
}
