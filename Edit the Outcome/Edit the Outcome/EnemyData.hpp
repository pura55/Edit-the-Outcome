#pragma once
#include <Siv3D.hpp>

/// <summary>
/// エネミーデータ
///
/// エネミーの情報を格納する構造体
/// <summary>
struct EnemyData
{
	int32 id;      //ID
	String name;   //名前
	int32 maxHp;   //体力
	int32 atk;     //攻撃力
};
