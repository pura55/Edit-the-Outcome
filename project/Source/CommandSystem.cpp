#include "CommandSystem.h"
#include "BattleSystem.h"

CommandSystem::CommandSystem() : battleSystem(nullptr)//参照をnullptrで初期化
{
	//列挙体の初期化
	currentCommandState = CommandState::Init;
	currentCommandType = CommandType::Init;

	//メンバー変数の初期化
	currentCommandIndex = 0;
	currentRecastTime = 0.0f;
	isRecastEnd = true;
	isCommandDecide = false;
	isCommandConfirme = false;
}

CommandSystem::~CommandSystem()
{
}

void CommandSystem::Update()
{
	switch (currentCommandState)
	{
	case CommandState::Init:
		currentCommandState = CommandState::Idle;
		break;
		
	case CommandState::Idle:
		currentCommandState = CommandState::Idle;
		break;

	case CommandState::Active:
		SelectCommand();
		if (isCommandConfirme)//コマンドが確定したら、Idleに移行する
		{
			currentCommandState = CommandState::Idle;
			//プレイヤーの入力が終了したことを伝える
			battleSystem->SetPlayerInputEnd(true);
		}
		break;
	}
	//リキャストタイマーを更新
	RecastTimer();
}

void CommandSystem::Draw()
{
}

void CommandSystem::SetReference()
{
	//// BattleSystem の参照を取得
	battleSystem = FindGameObject<BattleSystem>();
}

void CommandSystem::SelectCommand()
{
	if (!isCommandDecide)
	{
		//リキャスト時間が終了している場合、コマンドの選択を受け付ける
		if (isRecastEnd)
		{
			//[W]Keyでコマンドを上に移動、[S]Keyでコマンドを下に移動
			if (CheckHitKey(KEY_INPUT_W))
			{
				//コマンドのインデックスを減らす
				currentCommandIndex -= 1;
				//リキャスト時間をリセットする
				isRecastEnd = false;
				currentRecastTime = commandRecastTime;
				//コマンドのインデックスが0未満にならないようにする
				if (currentCommandIndex < 0)
				{
					currentCommandIndex = 0;
				}
			}
			if (CheckHitKey(KEY_INPUT_S))
			{
				//コマンドのインデックスを増やす
				currentCommandIndex += 1;
				//リキャスト時間をリセットする
				isRecastEnd = false;
				currentRecastTime = commandRecastTime;
				//コマンドのインデックスが2より大きくならないようにする
				if (currentCommandIndex > 2)
				{
					currentCommandIndex = 2;
				}
			}
			//[SPACE]Keyで決定
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				isCommandDecide = true;
				currentRecastTime = commandRecastTime;
			}
		}
	}
	else
	{
		//リキャスト時間が終了している場合、コマンドの選択を受け付ける
		if (isRecastEnd)
		{
			//[F]Keyで選択宣言を読み終える
			if (CheckHitKey(KEY_INPUT_F))
			{
				SetIsCommandConfirme(true);
				currentRecastTime = commandRecastTime;
			}
		}
	}
}

void CommandSystem::RecastTimer()
{
	//リキャスト時間が終了していない場合はリキャスト時間を減らす
	if (!isRecastEnd)
	{
		if (currentRecastTime > 0.0f)
		{
			currentRecastTime -= Time::DeltaTime();
		}
		else
		{
			//リキャスト時間が終了したら、タイマーが0いかにならないように設定し、リキャストフラグを終了にする
			currentRecastTime = 0.0f;
			isRecastEnd = true;
		}
	}
}

void CommandSystem::ResetCommand()
{
	SetIsCommandConfirme(false);
	SetIsCommandDecide(false);
	currentCommandIndex = 0;
	currentRecastTime = 0.0f;
	isRecastEnd = true;
}
