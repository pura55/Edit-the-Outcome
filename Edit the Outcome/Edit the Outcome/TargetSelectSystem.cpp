#include "stdafx.h"
#include "TargetSelectSystem.hpp"
#include "Player.hpp"

TargetSelectSystem::TargetSelectSystem()
{
}

void TargetSelectSystem::TargetSelect(const int32& maxEnemiesNum, const int32& mixEnemiesNum, const std::vector<int32>& exclusionEnemiesNum, int32& selectIndex, bool& isSelected, Player* player)
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

		//コマンドのインデックスが0未満にならないようにする
		if (selectIndex < 0)
		{
			selectIndex = 0;
		}
	}
	if (KeyD.down())
	{
		//選択のインデックスを増やす
		selectIndex += 1;

		// 敵の要素数からコマンドのインデックスの最大値を決める
		int32 maxIndex = maxEnemiesNum -1;

		//コマンドのインデックスが最大値より大きくならないようにする
		if (selectIndex > maxIndex)
		{
			selectIndex = maxIndex;
		}
	}
}
