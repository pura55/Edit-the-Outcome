#pragma once
#include <Siv3D.hpp>

class TargetSelectSystem
{
public:
	TargetSelectSystem();

	/// @brief 攻撃するターゲットを選択する関数
	void TargetSelect(const int32& maxEnemiesNum, int32& selectIndex, bool& isSelected);

private:
	
};
