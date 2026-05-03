#include "Common.h"

Common::Common()
{
	DontDestroyOnSceneChange();
	imageLoader = FindGameObject<ImageLoader>();
	if (!imageLoader)
	{
		imageLoader = new ImageLoader();
	}
}

Common::~Common()
{
}

void Common::Update()
{
}
