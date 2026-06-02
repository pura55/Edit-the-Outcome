#include "stdafx.h"
#include "BattleBgRenderer.hpp"

BattleBgRenderer::BattleBgRenderer()
{
}

void BattleBgRenderer::update()
{

}

void BattleBgRenderer::draw() const
{
	/// 背景 ///
	TextureAsset(U"BattleBg").drawAt(Scene::Center());
}
