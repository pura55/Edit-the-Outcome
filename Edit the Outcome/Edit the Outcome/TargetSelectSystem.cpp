#include "stdafx.h"
#include "TargetSelectSystem.hpp"
#include "Player.hpp"

TargetSelectSystem::TargetSelectSystem()
{
}

void TargetSelectSystem::TargetSelect(const int32& maxEnemiesNum, const int32& minEnemiesNum, const std::vector<int32>& exclusionEnemiesNum, int32& selectIndex, bool& isSelected, Player* player)
{
	if (KeySpace.down())
	{
		isSelected = true;
		// 状態を攻撃へ設定
		player->SetActionState(2);
	}

	//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
	if (KeyA.down())
	{
		//コマンドのインデックスを減らす
		selectIndex -= 1;

		// selectIndexと除外番号が一致している場合selectIndexを一つ飛ばす
		for (size_t i = 0; i < exclusionEnemiesNum.size(); i++)
		{
			if (exclusionEnemiesNum[i] == selectIndex)
			{
				selectIndex -= 1;
			}
		}

		//コマンドのインデックスが最小値未満にならないようにする
		if (selectIndex < minEnemiesNum)
		{
			selectIndex = minEnemiesNum;
		}
	}
	if (KeyD.down())
	{
		//選択のインデックスを増やす
		selectIndex += 1;

		// selectIndexと除外番号が一致している場合selectIndexを一つ飛ばす
		for (size_t i = 0; i < exclusionEnemiesNum.size(); i++)
		{
			if (exclusionEnemiesNum[i] == selectIndex)
			{
				selectIndex += 1;
			}
		}

		//コマンドのインデックスが最大値より大きくならないようにする
		if (selectIndex > maxEnemiesNum)
		{
			selectIndex = maxEnemiesNum;
		}
	}
}
