#include "stdafx.h"
#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init) : ProjectApp::Scene{init}
{
}

void TitleScene::update()
{
	if (KeyEscape.pressed())
	{
		System::Exit();
	}
}

void TitleScene::draw() const
{
	// タイトル描画
	FontAsset(U"TitleFont")(U"TitleScene")
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });
}
