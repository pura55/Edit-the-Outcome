#include "ImageLoader.h"

ImageLoader::ImageLoader()
{
	DontDestroyOnSceneChange();
	commandWindow = LoadGraph("Data/image/CommandWindowSmall.png");
	assert(commandWindow > 0);
}

ImageLoader::~ImageLoader()
{
	DeleteGraph(commandWindow);
}

void ImageLoader::Update()
{
}
