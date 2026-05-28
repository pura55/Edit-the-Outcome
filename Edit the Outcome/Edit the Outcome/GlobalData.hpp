#pragma once
#include "ImageLoader.hpp"

class GlobalData
{
public:
	GlobalData();
	void update();
	void init();

public:
	ImageLoader imageLoader;
};
