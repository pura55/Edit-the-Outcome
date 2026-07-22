#include "stdafx.h"
#include "TargetSelectSystem.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

TargetSelectSystem::TargetSelectSystem() : m_exclusionEnemiesNum{}, m_enemies{}
{	
}

void TargetSelectSystem::SetReference(Player* player, std::vector<Enemy*> enemies)
{
	// 参照を登録
	m_player = player;
	m_enemies = enemies;

	// 敵の参照が登録された際に除外の初期設定や最大値の設定も行う
	InitExclusionEnemies();
	RegistMaxEnemiesNum();
}

void TargetSelectSystem::TargetSelect(int32& selectIndex, bool& isSelected)
{
	if (KeySpace.down())
	{
		isSelected = true;
		// 状態を攻撃へ設定
		m_player->SetActionState(PlayerActionState::PlayerAttack);
	}

	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyA.down())
	{
		//コマンドのインデックスを減らす
		selectIndex -= 1;

		// selectIndexと除外番号が一致している場合selectIndexを一つ飛ばす
		for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
		{
			if (m_exclusionEnemiesNum[i] == selectIndex)
			{
				selectIndex -= 1;
			}
		}

		//コマンドのインデックスが最小値未満にならないようにする
		if (selectIndex < m_minEnemiesNum)
		{
			selectIndex = m_minEnemiesNum;
		}
	}
	if (KeyD.down())
	{
		//選択のインデックスを増やす
		selectIndex += 1;

		// selectIndexと除外番号が一致している場合selectIndexを一つ飛ばす
		for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
		{
			if (m_exclusionEnemiesNum[i] == selectIndex)
			{
				selectIndex += 1;
			}
		}

		//コマンドのインデックスが最大値より大きくならないようにする
		if (selectIndex > m_maxEnemiesNum)
		{
			selectIndex = m_maxEnemiesNum;
		}
	}
}

void TargetSelectSystem::InitExclusionEnemies()
{
	m_exclusionEnemiesNum.resize(m_enemies.size());// 敵の配列のサイズをコピー

	// 除外する敵の番号に初期値として例外番号（-1）を格納
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		m_exclusionEnemiesNum[i] = -1;
	}
}

void TargetSelectSystem::ExclusionEnemies(int32& selectIndex)
{
	// 除外するターゲットを設定
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		if (m_enemies[i]->GetIsDead())
		{
			m_exclusionEnemiesNum[i] = m_enemies[i]->GetGenerateNum();
		}
	}

	bool decideMinEnemy = false;
	bool decideMaxEnemy = false;

	// 敵を除外後の最小値を設定
	for (size_t i = 0; i < m_exclusionEnemiesNum.size(); i++)
	{
		if (not decideMinEnemy)
		{
			// 除外設定がされていない場合その番号を最小値とする
			if (m_exclusionEnemiesNum[i] == -1)
			{
				m_minEnemiesNum = i; // iと生成番号が一致しているためiを代入
				selectIndex = m_minEnemiesNum;  // 最小値をターゲットインデックスに適用
				decideMinEnemy = true; // 最小値設定完了
				break;
			}
		}
	}

	// 除外されていなかった場合最小値を0
	if (not decideMinEnemy)
	{
		m_minEnemiesNum = 0;
		selectIndex = m_minEnemiesNum;
		decideMinEnemy = true;
	}

	// 敵を除外後の最大値を設定
	for (size_t i = m_exclusionEnemiesNum.size(); i > 0; i--)
	{
		size_t j = i - 1;

		if (not decideMaxEnemy)
		{
			// 除外設定がされていない場合その番号を最大値とする
			if (m_exclusionEnemiesNum[j] == -1)
			{
				m_maxEnemiesNum = j; // jと生成番号が一致しているためjを代入

				decideMaxEnemy = true; // 最大値設定完了
				break;
			}
		}
	}

	// 除外されていなかった場合最大値をサイズと同様
	if (not decideMaxEnemy)
	{
		m_maxEnemiesNum = m_exclusionEnemiesNum.size() - 1;
		decideMaxEnemy = true;
	}
}
