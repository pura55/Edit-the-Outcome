#include "stdafx.h"
#include "TitleUI.hpp"

TitleUI::TitleUI()
{
}

void TitleUI::update()
{
	isKeyDownB();
	isKeyDownEscape();
}

void TitleUI::draw()const
{
	// タイトル描画
	FontAsset(U"TitleFont")(U"TitleScene")
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });
}

bool TitleUI::isKeyDownB()
{
	//[B]keyが押されたら
	if (KeyB.down())
	{
		return true;
	}
	return false;
}

bool TitleUI::isKeyDownEscape()
{
	//[Escape]keyが押されたら
	if (KeyEscape.down())
	{
		return true;
	}
	return false;
}
