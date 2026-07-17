#include "stdafx.h"
#include "LootBg.hpp"

LootBg::LootBg()
{
}

void LootBg::update()
{

}

void LootBg::draw() const
{
	TextureAsset(U"LootBgMagic").drawAt(Scene::Center());
}
