#include "stdafx.h"
#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init) : ProjectApp::Scene{init}
{
}

void TitleScene::update()
{
	//update
	m_ui.update();

	if (m_ui.isPlayButtonPush())
	{
		//バトルシーンへ遷移
		changeScene(State::CutScene);
		return;
	}
	if (m_ui.isEndButtonPush())
	{
		//ゲームを終了
		System::Exit();
		return;
	}
	
}

void TitleScene::draw() const
{
	m_ui.draw();
}
