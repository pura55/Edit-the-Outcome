#pragma once
#include <Siv3D.hpp>

// 前方宣言
class HealthManager;
class Enemy;
class Player;

/// <summary>
/// エネミーアクションマネージャー
///
/// 敵の攻撃を管理するクラス
/// </summary>
class EnemyActionManager
{
public:
	EnemyActionManager();

	/// @brief 参照を登録する関数
	void SetReference(HealthManager& healhManager, std::vector<Enemy*>& enemies);

	/// @brief エネミーをキューに入れる関数
	void SetEnemyQueue();

	/// @brief エネミーの行動処理を実行する関数
	void ExecuteActionProcess(const Player* player);

	/// @brief 敵の行動フラグを返す関数
	bool GetEnemyAct() const { return m_isEnemyAct; }

	/// @brief 敵の行動フラグを設定する関数
	/// @param act 設定するフラグ
	void SetEnemyAct(bool act) { m_isEnemyAct = act; }

private:
	HealthManager* m_healthManager{ nullptr }; // ヘルスマネージャーの参照

	std::vector<Enemy*> m_enemies{ nullptr }; // エネミーの参照

	std::queue<Enemy*> m_enemiesQueue; // エネミーのキュー

	bool m_isEnemyAct{ false }; // 敵の行動フラグ
};
