#pragma once
# include <Siv3D.hpp>
# include "GlobalData.hpp"

///<summary>
/// シーンのステート
///</summary>
enum class State
{
	TitleScene
};

///<summary>
/// 共有するデータ
///</summary>
struct GameData
{
	//グローバルデータ
	GlobalData globalData;
};

using ProjectApp = SceneManager<State, GameData>;
