#pragma once
#include <Siv3D.hpp>

class HealthManager;
class Enemy;
class Player;

class EnemyActionManager
{
public:
	EnemyActionManager();

	/// @brief 参照を登録する関数
	void SetReference(HealthManager& healhManager, std::vector<Enemy*> enemies);

	/// @brief エネミーをキューに入れる関数
	void SetEnemyQueue();

	/// @brief エネミーの行動処理を実行する関数
	void ExecuteActionProcess(bool& isActed, const Player* player);

private:
	HealthManager* m_healthManager{ nullptr }; // ヘルスマネージャーの参照

	std::vector<Enemy*> m_enemies{ nullptr }; // エネミーの参照

	std::queue<Enemy*> m_enemiesQueue; // エネミーのキュー
};
