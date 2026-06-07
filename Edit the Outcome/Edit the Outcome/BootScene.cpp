#include "stdafx.h"
#include "BootScene.hpp"

BootScene::BootScene(const InitData& init) : ProjectApp::Scene{init}
{
	if (getData().globalData.LoadAllData())
	{
		m_isLoadFinished = true;
	}
	else
	{
		System::Exit();
	}
	
}

void BootScene::update()
{
	// ロードが完了したら
	if (m_isLoadFinished)
	{
		// タイトルシーンへ遷移
		changeScene(State::TitleScene);
	}
}

void BootScene::draw() const
{
}
