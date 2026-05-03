#include "BattleUI.h"

BattleUI::BattleUI()
{
}

BattleUI::~BattleUI()
{
}

void BattleUI::Update()
{
}

void BattleUI::Draw()
{
	DrawRectGraph(200, 400, 0, 0, 512, 192, imageLoader->GetCommandWindow(), TRUE);
}
