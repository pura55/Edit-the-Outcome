#pragma once
#include <Siv3D.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "GlobalData.hpp"
#include "PlayerProgressData.hpp"
#include "EnemyData.hpp"
#include "RandomEngine.hpp"

/// <summary>
/// スポナー
///
/// キャラクターを生成するクラス
/// </summary>
class Spawner
{
public:
	Spawner() {};

	/// @brief プレイヤーを生成する関数
	/// @return プレイヤーのインスタンス
	std::unique_ptr<Player> GeneratePlayer(const int32 id, const std::vector<PlayerProgressData> data);

	/// @brief エネミーを生成する関数
    /// @return エネミーのインスタンス
	std::vector<std::unique_ptr<Enemy>> GenerateEnemies(const int32 round, GlobalData data, RandomEngine& randomEngine);

private:
	int32 TypeOfEnemy(const int32 round, RandomEngine& randomEngine);
};
