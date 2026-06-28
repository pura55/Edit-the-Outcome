#pragma once
#include <Siv3D.hpp>

// 前方宣言
class Player;
class Enemy;

class HealthManager
{
public:
	HealthManager();

	/// @brief 外部オブジェクトへの参照を設定する関数
	void SetReference(Player* player, std::vector<Enemy*> enemies);

	/// ダメージ関数 ///
#pragma region Damage
	/// @brief プレイヤーからエネミーへのダメージを計算して設定する関数
	void PlayerAttackEnemy(int32 playerAtk, int32 enemyGenerateNum);

	/// @brief エネミーからプレイヤーへのダメージを計算して設定する関数
	void EnemyAttackPlayer(int32 enemyAtk, int32 playerHp);
#pragma endregion

private:
	Player* m_player{ nullptr };
	std::vector<Enemy*> m_enemies{ nullptr };
};
