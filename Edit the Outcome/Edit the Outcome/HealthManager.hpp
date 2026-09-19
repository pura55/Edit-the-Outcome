#pragma once
#include <Siv3D.hpp>

// 前方宣言
class Player;
class Enemy;
class BattleUI;

/// <summary>
/// ヘルスマネージャー
/// 
/// 体力変動を管理するクラス
/// </summary>
class HealthManager
{
public:
	HealthManager();

	/// @brief 外部オブジェクトへの参照を設定する関数
	void SetReference(Player* player, const std::vector<Enemy*>& enemies, BattleUI& battleUI);

	/// ダメージ関数 ///
#pragma region Damage
	/// @brief プレイヤーからエネミーへのダメージを計算して設定する関数
	void PlayerAttackEnemy(int32 playerAtk, int32 enemyGenerateNum);

	/// @brief プレイヤーからエネミーへのダメージを計算して設定する関数(スキルver）
	void PlayerSkillEnemy(int32 playerAtk, int32 enemyGenerateNum, int32 skillNums);

	/// @brief エネミーからプレイヤーへのダメージを計算して設定する関数
	void EnemyAttackPlayer(int32 enemyAtk);
#pragma endregion

private:
	Player* m_player{ nullptr };
	std::vector<Enemy*> m_enemies{ nullptr };
	BattleUI* m_battleUI{ nullptr };


	const double m_damageReflectionTime{ 1.0 }; // ダメージを影響させる間隔

	double m_currentReflectionTime{ 0 }; // 現在の影響時間

	int32 m_reflectionCount{ 0 }; // 影響を与えた回数
};
