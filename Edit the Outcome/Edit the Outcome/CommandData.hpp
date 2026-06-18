#pragma once
#include <Siv3D.hpp>

/// <summary>
/// エネミーデータ
///
/// エネミーの情報を格納する構造体
/// <summary>
struct CommandData
{
	int32 id;      // ID
	String name;   // 名前
	int32 dmg;     // ダメージ
};

