#include "stdafx.h"
#include "BattleSystem.hpp"
#include "CommandManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

BattleSystem::BattleSystem()
{
}

void BattleSystem::update(CommandManager& commandManager)
{
	switch (m_state)
	{
	case BattleState::Init:
		StateInit(commandManager);
		break;

	case BattleState::Start:
		if (StateStart())
			m_state = BattleState::CommandInput;
		break;

	case BattleState::CommandInput:
		//プレイヤーが入力を終えたら、EnemyActionに移行する
		//未確定の場合は留まる
		StateCommandInput(commandManager);
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
}

void BattleSystem::SetReference(Player* player)
{
	// プレイヤーの参照を取得
	m_player = player;

	// エネミーの参照を取得
	//m_enemy = &enemy;
}

void BattleSystem::StateInit(CommandManager& commandManager)
{
	m_state = BattleState::Start;
	// コマンドマネージャーで敵の数を登録する
	commandManager.RegistMaxEnemiesNum();
}

bool BattleSystem::StateStart()
{
	if (Key1.down())
	{
		return true;
	}
	return false;
}

void BattleSystem::StateCommandInput(CommandManager& commandManager)
{
	if (m_isSelected)
	{
		m_state = BattleState::EnemyAction;
		commandManager.ResetVariable();
		return;
	}

	// コマンド処理を更新
	commandManager.UpdateCommandProcess(m_isSelected);
}

bool BattleSystem::StateEnemyAction()
{
	if (Key3.down())
	{
		return true;
	}
	return false;
}

void BattleSystem::StateTurnEnd()
{
	
	m_isSelected = false;
	// 敵のHpが0だったらバトルを終了
	if (Key5.down())
	{
		m_state = BattleState::BattleEnd;
		return;
	}
	// プレイヤーのHpが0だったらバトルを終了
	if (Key6.down())
	{
		m_state = BattleState::BattleEnd;
		return;
	}

	m_state = BattleState::CommandInput;
	
}

void BattleSystem::StateBattleEnd()
{
	if (KeyT.down())
	{
		m_isBattleEnd = true;
	}
	else
	{
	}
}


