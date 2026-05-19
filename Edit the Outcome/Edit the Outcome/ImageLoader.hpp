#pragma once
#include <Siv3D.hpp>

class ImageLoader
{
private:
	HashTable<String, Texture> m_imageTable;

public:
	ImageLoader();
	void init();
};


