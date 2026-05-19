#include "stdafx.h"
#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init) : ProjectApp::Scene{init}
{
}

void TitleScene::update()
{
	//update
	m_ui.update();
	m_ui.draw();

	if (m_ui.isKeyDownB())
	{
		//バトルシーンへ遷移
		changeScene(State::BattleScene);
	}
	if (m_ui.isKeyDownEscape())
	{
		//ゲームを終了
		System::Exit();
	}
}

void TitleScene::draw() const
{
	
}
