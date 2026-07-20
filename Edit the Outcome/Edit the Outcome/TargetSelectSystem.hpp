#pragma once
#include <Siv3D.hpp>

class Player;

/// <summary>
/// ターゲットセレクトシステム
///
/// 敵を選択する処理を行うクラス
/// </summary>
class TargetSelectSystem
{
public:
	TargetSelectSystem();

	/// @brief 攻撃するターゲットを選択する関数
	void TargetSelect(const int32& maxEnemiesNum, const int32& mixEnemiesNum, const std::vector<int32>& exclusionEnemiesNum, int32& selectIndex, bool& isSelected, Player* player);

private:
	
};
