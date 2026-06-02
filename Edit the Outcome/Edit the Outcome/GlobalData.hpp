#pragma once
#include "ImageLoader.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class GlobalData
{
public:
	GlobalData();
	void update();
	void init();

public:
	ImageLoader imageLoader;
	Player player;
	Enemy enemy;
};
