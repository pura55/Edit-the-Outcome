#pragma once
#include "CommandData.hpp"
#include "PlayerProgressData.hpp"

/// <summary>
/// ルートアイテムデータ
///
/// ルートアイテムのデータを格納する構造体
/// </summary>
struct LootItemData
{
	/// @brief std::variant(指定した複数の型のうち、いずれか1つの値を型安全に保持できる機能)
	/// @brief を使用し

	// ルートデータを格納する変数
	std::variant<CommandData, PlayerProgressData> lootData;
};
