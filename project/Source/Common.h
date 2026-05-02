#pragma once
#include "../Library/GameObject.h"
#include "ImageLoader.h"

class Common : public GameObject
{
public:
	Common();
	~Common();
	void Update() override;

private:
	ImageLoader* imageLoader = FindGameObject<ImageLoader>();
};
