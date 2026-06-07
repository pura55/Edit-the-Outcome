#pragma once
#include <Siv3D.hpp>

/// <summary>
/// プレイヤープログレスデータ
///
/// プレイヤーの情報を格納する構造体
/// <summary>
struct PlayerProgressData
{
	int32 id;     //ID
	String name;  //名前
	int32 maxHp;  //体力
	int32 atk;    //攻撃力
};
