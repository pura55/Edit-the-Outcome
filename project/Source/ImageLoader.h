#pragma once
#include "../Library/GameObject.h"

class ImageLoader : public GameObject
{
public:
	ImageLoader();
	~ImageLoader();
	void Update() override;

public:
	int GetCommandWindow() const{ return commandWindow; }
private:
	int commandWindow = LoadGraph("Data/image/CommandWindow.png");
};