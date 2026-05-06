#include "ImageLoader.h"

ImageLoader::ImageLoader()
{
	DontDestroyOnSceneChange();
	commandWindow = LoadGraph("Data/image/CommandWindowSmall.png");
	assert(commandWindow > 0);
	forestBg = LoadGraph("Data/image/ForestBg.jpg");
	assert(forestBg > 0);
}

ImageLoader::~ImageLoader()
{
	DeleteGraph(commandWindow);
	DeleteGraph(forestBg);
}

void ImageLoader::Update()
{
}
