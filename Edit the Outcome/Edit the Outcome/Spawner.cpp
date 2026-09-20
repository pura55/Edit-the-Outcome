#include "stdafx.h"
#include "Spawner.hpp"
std::unique_ptr<Player> Spawner::GeneratePlayer(const int32 id, const std::vector<PlayerProgressData> data)
{
	// プレイヤーのデータから該当するidを探す
	for (const auto& progress : data)
	{
		// IDが一致している場合そのデータをプレイヤーに渡す
		if (progress.id == id)
		{
			return std::make_unique<Player>(progress);
		}
	}

	// 見つからない場合の例外処理
	throw Error{ U"GameDataのplayerProgressList内に、ID: {} のプレイヤーデータが存在しません！初期化漏れの可能性があります。"_fmt(id) };
	return nullptr;
}

std::vector<std::unique_ptr<Enemy>> Spawner::GenerateEnemies(const int32 round,GlobalData data, RandomEngine& randomEngine)
{
	int32 numOfTimes = randomEngine.RandomInt32(1, 3); //Random<int32>(1, 3); // 生成する回数

	// エネミーの容器
	std::vector<std::unique_ptr<Enemy>> enemies;

	// 生成カウントが回数に達したら生成終了
	for (int32 generateCount = 0; generateCount < numOfTimes; generateCount++)
	{
		int32 generateId = TypeOfEnemy(round, randomEngine); // 生成するエネミーのid

		// 敵の生成
		// エネミーのデータと生成番号(generateCount)を渡す
		enemies.push_back(std::make_unique<Enemy>(data.GetEnemyData(generateId), generateCount));
	}

	// 生成したエネミーを返す
	return enemies;
}

int32 Spawner::TypeOfEnemy(const int32 round, RandomEngine& randomEngine)
{
	//「ID：1スライム」,「ID：２オーク」
	int32 generateId;

	switch (round)
	{
	case 1:
		generateId = randomEngine.RandomInt32(1, 2);
		break;
	case 2:
		generateId = randomEngine.RandomInt32(1, 2);
		break;
	case 3:
		generateId = randomEngine.RandomInt32(1, 2);
		break;
	case 4:
		generateId = randomEngine.RandomInt32(3, 4);
		break;
	case 5:
		generateId = randomEngine.RandomInt32(3, 4);
		break;
	case 6:
		generateId = randomEngine.RandomInt32(3, 4);
		break;
	case 7:
		generateId = randomEngine.RandomInt32(5, 6);
		break;
	case 8:
		generateId = randomEngine.RandomInt32(5, 6);
		break;
	case 9:
		generateId = randomEngine.RandomInt32(5, 6);
		break;
	default:
		generateId = 0;
		break;
	}

	return generateId;
}
