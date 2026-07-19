#include "stdafx.h"
#include "LootUI.hpp"]
#include "LootSystem.hpp"

LootUI::LootUI()
{
}

void LootUI::update()
{
	// メニューの状態で更新する処理を分ける
	switch (m_lootSystem->GetMenuState())
	{
	case 0:
		UpdateSelectCursor();
		break;
	case 1:
		UpdateCheckCursor();
		break;
	case 2:
		break;
	}
	
}

void LootUI::draw() const
{
	// ドワーフとテキストの描画
	TextureAsset(U"DwarfKind").drawAt(m_dwarfPos);
	TextureAsset(U"SpeechFrame").drawAt(m_speechFramePos);

	for (int32 i = 0; i < 3; i++)
	{
		// ルートフレームの描画
		TextureAsset(U"LootItemFrame").drawAt(m_itemFramePos.x + i*320, m_itemFramePos.y);
	}
	// 選択画面だった場合描画
	if (m_lootSystem->GetMenuState() == 0)
	{
		// 選択用カーソルの描画
		TextureAsset(U"LootCursor").drawAt(m_movedSelectPos);
	}

	// 選択画面じゃない場合描画
	if (m_lootSystem->GetMenuState() != 0)
	{
		// 獲得確認のフレームの描画
		TextureAsset(U"LootCheckFrame").drawAt(m_checkFramePos.x, m_checkFramePos.y);

		for (int32 i = 0; i < 2; i++)
		{
			TextureAsset(U"CheckButton").drawAt(m_checkButtonPos.x + i*140.0, m_checkButtonPos.y);
			switch(i)
			{
			case 0:
				FontAsset(U"LootItemCheck")(U"はい")
					.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), m_checkButtonPos.x + i * 140.0, m_checkButtonPos.y - 5.0);
				break;
			case 1:
				FontAsset(U"LootItemCheck")(U"いいえ")
					.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), m_checkButtonPos.x + i * 140.0, m_checkButtonPos.y - 5.0);
				break;
			}
			
		}

		// 確認カーソルの描画
		TextureAsset(U"LootCursor").drawAt(m_movedCheckPos);
	}
}

void LootUI::SetReference(LootSystem& lootSystem)
{
	m_lootSystem = &lootSystem;
}

void LootUI::UpdateSelectCursor()
{
	// 選択肢数による移動量の設定
	m_currentSelectIndex = m_lootSystem->GetSelectIndex();
	m_offsetSelectCursorX = (m_currentSelectIndex * 320.0);

	// 時間経過によりcosを動かす
	double cosLoopTime = Scene::Time() * 2.5;
	m_cosWave = Math::Cos(cosLoopTime) * 10.0;

	// 移動後の座標を設定
	m_movedSelectPos = m_selectCursorPos.movedBy(m_offsetSelectCursorX + m_cosWave , m_cosWave);
}

void LootUI::UpdateCheckCursor()
{
	// 確認指数による移動量の設定
	m_currentCheckIndex = m_lootSystem->GetCheckIndex();
	m_offsetCheckCursorX = (m_currentCheckIndex * 140.0);

	// 時間経過によりcosを動かす
	double cosLoopTime = Scene::Time() * 2.5;
	m_cosWave = Math::Cos(cosLoopTime) * 10.0;

	// 移動後の座標を設定
	m_movedCheckPos = m_checkCursorPos.movedBy(m_offsetCheckCursorX + m_cosWave, m_cosWave);
}


