#pragma once
# include <Siv3D.hpp>

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
};

using ProjectApp = SceneManager<State, GameData>;
