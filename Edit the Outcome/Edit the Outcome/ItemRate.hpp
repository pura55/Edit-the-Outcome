#pragma once

/// <summary>
/// アイテムレート
///
/// アイテム出現の確率を定義する名前空間
/// </summary>
namespace ItemRate
{
	/// 最小最大 ///

	const double DOUBLE_MAX{ 1.0 }; // double型の確率の最大値
	const double DOUBLE_MIN{ 0.0 }; // double型の確率の最小値

	/// アイテムの種類別の出現確率 ///

	const double COMMAND_APPEARING{ 0.25 }; // コマンドの出現確率

	// ステータス上昇の出現確率 ＊出現は二択であるため定義しない
    // STAT_APPEARING{ 0.75 }; 
	


	/// コマンド別の出現確率 ///

	const double COMMAND_AVG{ 0.25 }; // １コマンド当たりの平均確率

	/// ステータス別の出現確率 ///

	const double STAT_AVG{ 0.25 }; // １ステータス当たりの平均確率
}
