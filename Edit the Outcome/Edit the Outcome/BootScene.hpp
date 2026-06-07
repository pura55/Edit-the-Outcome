#pragma once
#include "Common.hpp"

class BootScene : public ProjectApp::Scene
{
public:
	BootScene(const InitData& init);
	void update() override;
	void draw() const override;

	// フェードインを行わない
	void drawFadeIn(double) const override {
		draw();
	}
private:
	// ロードが完了したかどうかのフラグ
	bool m_isLoadFinished{ false };

};
