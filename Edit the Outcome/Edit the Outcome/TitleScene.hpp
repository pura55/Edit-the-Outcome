#pragma once
#include "Common.hpp"

///<summary>
/// タイトルシーン
///</summary>
class TitleScene : public ProjectApp::Scene
{
public:
	TitleScene(const InitData& init);
	void update() override;
	void draw() const override;
};
