#include "stdafx.h"
#include "BattleSystem.hpp"
#include "CommandManager.hpp"
#include "EnemyActionManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "BattleUI.hpp"

BattleSystem::BattleSystem()
{
}

void BattleSystem::update(CommandManager& commandManager, EnemyActionManager& enemyActionManager, BattleUI& battleUI)
{
	switch (m_state)
	{
	case BattleState::Init:
		StateInit(commandManager, enemyActionManager);
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
		if (StateEnemyAction(enemyActionManager))
			m_state = BattleState::TurnEnd;
		break;

	case BattleState::TurnEnd:
		//ターン終了の処理が終わったら、PlayerInputに移行する
		//バトルを終了する場合は、BattleEndに移行する
		StateTurnEnd(commandManager, enemyActionManager,battleUI);
		break;

	case BattleState::BattleEnd:
		StateBattleEnd();
		break;
	}
}

void BattleSystem::SetReference(Player* player, const std::vector<Enemy*>& enemies)
{
	// プレイヤーの参照を取得
	m_player = player;

	// エネミーの参照を取得
	m_enemies = enemies;
}

void BattleSystem::StateInit(CommandManager& commandManager, EnemyActionManager& enemyActionManager)
{
	m_state = BattleState::CommandInput;
	// 変数を初期化
	commandManager.ResetVariable();

	// エネミーをキューに入れる
	enemyActionManager.SetEnemyQueue();
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
	if (commandManager.GetIsCommandSelected())
	{
		commandManager.PopMenuState();
		m_state = BattleState::EnemyAction;
		return;
	}

	// コマンド処理を更新
	commandManager.update();
}

bool BattleSystem::StateEnemyAction(EnemyActionManager& enemyActionManager)
{
	if (enemyActionManager.GetEnemyAct())
	{
		// エネミーをキューに入れる
		enemyActionManager.SetEnemyQueue();
		return true;
	}

	// エネミーの行動処理を実行
	enemyActionManager.ExecuteActionProcess(m_player);

	return false;
}

void BattleSystem::StateTurnEnd(CommandManager& commandManager, EnemyActionManager& enemyActionManager, BattleUI& battleUI)
{
	// 行動フラグをリセット
	commandManager.SetIsCommandSelected(false);
	enemyActionManager.SetEnemyAct(false);

	// コマンドマネージャーの変数をリセット
	commandManager.ResetVariable();

	bool isEnemiesDead = true;

	for (auto enemies : m_enemies)
	{
		// エネミーが死んでいるのであれば次の処理へ
		if (enemies->GetIsDead()) continue;

		// 死亡判定がfalseで帰ってきた時はisEnemyDeadをfalse
		isEnemiesDead = false;
	}

	// 敵が全員死亡していた場合バトルを終了
	if (isEnemiesDead)
	{
		m_state = BattleState::BattleEnd;
		m_isWin = true;
		battleUI.SetWin();
		return;
	}
	// プレイヤーのHpが0だったらバトルを終了
	if (m_player->GetIsDead())
	{
		m_state = BattleState::BattleEnd;
		m_isLose = true;
		battleUI.SetLose();
		return;
	}

	if (m_player->GetPlayerHp() == 0) return;

	m_state = BattleState::CommandInput;
	return;
}

void BattleSystem::StateBattleEnd()
{
	if (KeySpace.down())
	{
		m_isBattleEnd = true;
	}
}


