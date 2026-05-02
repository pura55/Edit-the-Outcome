#include "CommandSystem.h"

CommandSystem::CommandSystem()
{
}

CommandSystem::~CommandSystem()
{
}

void CommandSystem::Update()
{
}

void CommandSystem::Draw()
{
	DrawRectGraph(200, 400, 0, 0, 512, 192, imageLoader->GetCommandWindow(), TRUE);
}
