#include "stdafx.h"
#include "TargetSelectSystem.hpp"

TargetSelectSystem::TargetSelectSystem()
{
}

void TargetSelectSystem::TargetSelect(const int32& maxEnemiesNum, int32& selectIndex, bool& isSelected)
{
	if (KeySpace.down())
	{
		isSelected = true;
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
