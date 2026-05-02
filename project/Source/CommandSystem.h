#pragma once
#include "../Library/GameObject.h"
#include "ImageLoader.h"

class CommandSystem : public GameObject
{
public:
	CommandSystem();
	~CommandSystem();
	void Update()override;
	void Draw()override;

private:
	ImageLoader* imageLoader = FindGameObject<ImageLoader>();
};