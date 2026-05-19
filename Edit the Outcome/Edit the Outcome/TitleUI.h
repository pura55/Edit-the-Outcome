#pragma once
#include <Siv3D.hpp>

class TitleUI
{
public:
	TitleUI();
	void update();
	void draw() const;
	bool isKeyDownB();
	bool isKeyDownEscape();
};
