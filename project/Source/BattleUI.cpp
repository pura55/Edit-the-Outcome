#include "BattleUI.h"

BattleUI::BattleUI()
{
	//imageLoaderとcommandSystemのインスタンスを取得
	imageLoader = FindGameObject<ImageLoader>();
	commandSystem = FindGameObject<CommandSystem>();
}

BattleUI::~BattleUI()
{
}

void BattleUI::Update()
{
	currentCommandIndex = commandSystem->GetCurrentCommandIndex();
}

void BattleUI::Draw()
{
	//森の背景を描画(現在は非表示)
	//DrawRectGraph(0, 0, 0, 0, 1920, 1080, imageLoader->GetForestBg(), TRUE);
	//コマンドウィンドウを描画
	DrawRectGraph(commandWindowPos.x, commandWindowPos.y, 0, 0, 512, 192, imageLoader->GetCommandWindow(), TRUE);
	//選択矢印を表示
	DrawTriangle(Triangle_FirstPos.x, Triangle_FirstPos.y + 32 * currentCommandIndex, Triangle_SecondPos.x, Triangle_SecondPos.y + 32 * currentCommandIndex,
		Triangle_ThirdPos.x, Triangle_ThirdPos.y + 32 * currentCommandIndex, GetColor(255, 255, 255), TRUE);
	SetFontSize(16);
	DrawString(Triangle_FirstPos.x + 32, Triangle_FirstPos.y, "攻撃", GetColor(255, 255, 255), TRUE);
	DrawString(Triangle_FirstPos.x + 32, Triangle_FirstPos.y + 32, "スキル", GetColor(255, 255, 255), TRUE);
	DrawString(Triangle_FirstPos.x + 32, Triangle_FirstPos.y + 32 * 2, "防御", GetColor(255, 255, 255), TRUE);
	SetFontSize(40);
}
