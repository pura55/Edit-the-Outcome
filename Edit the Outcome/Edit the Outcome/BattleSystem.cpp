#include "stdafx.h"
#include "BattleSystem.hpp"

BattleSystem::BattleSystem()
{
}

void BattleSystem::update()
{
	switch (m_state)
	{
	case BattleState::Init:
		StateInit();
		break;

	case BattleState::Start:
		if (StateStart())
			m_state = BattleState::CommandInput;
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
			m_state = BattleState::TurnEnd;
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
	FontAsset(U"BattleSystem")(m_currentStateText)
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });
}

void BattleSystem::StateInit()
{
	m_state = BattleState::Start;
	m_menuStack.push(MenuState::Base);
}

bool BattleSystem::StateStart()
{
	m_currentStateText = U"Start";
	if (Key1.down())
	{
		return true;
	}
	return false;
}

void BattleSystem::StateCommandInput()
{
	m_currentStateText = U"CommandInput";

	if (m_menuStack.top() == MenuState::Base)//ベースメニュー時
	{
		//コマンド操作
		SelectCommandIndex();
		//	現在のコマンドインデックス
		switch (m_currentCommandIndex)
		{
		case 0: //攻撃
			m_type = CommandType::Attack;
			break;

		case 1: //防御
			m_type = CommandType::Diffence;
			break;

		case 2: //スキル
			m_type = CommandType::Skills;
			break;
		}

		switch (m_type)
		{
		case CommandType::Attack: //攻撃選択時
			if (KeySpace.down())
			{
				m_state = BattleState::EnemyAction;
			}
			break;
		case CommandType::Diffence: //防御を選択時
			if (KeySpace.down())
			{
				m_state = BattleState::EnemyAction;
			}
			break;
		case CommandType::Skills: //スキルを選択時
			if (KeySpace.down())
			{
				m_currentCommandIndex = 0;
				//スキルのメニューへ移る
				m_menuStack.push(MenuState::Skill);
			}
			break;
		}
	}
	else if (m_menuStack.top() == MenuState::Skill) //スキルメニュー時
	{
		//コマンド操作
		SelectCommandIndex();
		if (KeySpace.down())
		{
			m_state = BattleState::EnemyAction;
		}
		if (KeyB.down())
		{
			m_currentCommandIndex = 1;
			//ベースのメニューへ戻る
			m_menuStack.pop();
		}
	}

}

bool BattleSystem::StateEnemyAction()
{
	m_currentStateText = U"EnemyAction";
	if (Key3.down())
	{
		return true;
	}
	return false;
}

void BattleSystem::StateTurnEnd()
{
	m_currentStateText = U"TurnEnd";
	if (Key4.down())
	{
		SetCommandInputEnd(false);
		m_state = BattleState::CommandInput;
	}
	if (Key5.down())
	{
		m_state = BattleState::BattleEnd;
	}
}

void BattleSystem::StateBattleEnd()
{
	if (KeyT.down())
	{
		m_currentStateText = U"BattleEnd:now pushing T";
		m_isBattleEnd = true;
	}
	else
	{
		m_currentStateText = U"BattleEnd";
	}
}

void BattleSystem::SelectCommandIndex()
{
	//コマンドメニュー内のコマンド数を設定
	if (m_menuStack.top() == MenuState::Base)
	{
		m_maxCommandIndex = 2;
	}
	else
	{
		m_maxCommandIndex = 2;
	}

	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyW.down())
	{
		//コマンドのインデックスを減らす
		m_currentCommandIndex -= 1;

		//コマンドのインデックスが1未満にならないようにする
		if (m_currentCommandIndex < m_minCommandIndex)
		{
			m_currentCommandIndex = m_minCommandIndex;
		}
	}
	if (KeyS.down())
	{
		//コマンドのインデックスを増やす
		m_currentCommandIndex += 1;

		//コマンドのインデックスが2より大きくならないようにする
		if (m_currentCommandIndex > m_maxCommandIndex-1)
		{
			m_currentCommandIndex = m_maxCommandIndex;
		}
	}
}
