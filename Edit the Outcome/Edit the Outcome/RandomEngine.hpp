#pragma once
#include <Siv3D.hpp>

/// <Summary>
/// ランダムエンジン
///
/// 乱数エンジン（mt19973）を保持するクラス
class RandomEngine
{
public:
	/// @param seed シード値をrngに格納
	RandomEngine(uint32 seed) : rng(seed) {}

	/// @brief int32型の乱数を返す関数
	/// @param min 最小値
	/// @param max 最大値
	/// @return 最小値以上、最大値以下の乱数
	int32 RandomInt32(int32 min, int32 max)
	{
		// 指定された範囲の実数（double）を等確率（一様分布）で生成する
		std::uniform_int_distribution<int32> dist(min, max);

		return dist(rng); // 指定範囲の中からシード値に従って乱数を返す
	}

	/// @brief double型の乱数を返す関数
	/// @param min 最小値
	/// @param max 最大値
	/// @return 最小値以上、最大値以下の乱数
	double RandomDouble(double min, double max)
	{
		// 指定された範囲の実数（double）を等確率（一様分布）で生成する
		std::uniform_real_distribution<double> dist(min, max);

		return dist(rng); // 指定範囲の中からシード値に従って乱数を返す
	}

private:
	// mt：Mersenne Twister（メルセンヌ・ツイスター）
	// シード値
	std::mt19937 rng;
};
