#include "stdafx.h"
#include "BattleUI.hpp"
#include "BattleSystem.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

BattleUI::BattleUI() :m_player{ nullptr }
{
}

void BattleUI::update()
{
	if (not m_battleSystem->GetIsSkillMenu())
	{
		// カーソルを更新
		UpdateCursorPos();
	}
	else
	{
		// サブのカーソルを更新
		UpdateSubCursorPos();
	}

	//ヘルスバーに表示するHpの割合を計算します
	playerHealthPct = fullHealthPct * (m_player->GetCurrentPlayerHp() / playerHealth);
	enemyHealthPct = fullHealthPct * (m_battleSystem->GetCurrentEnemyHp() / enemyHealth);
}

/// <remarks>
/// 描画に関する注意点を記述します。
///
/// アトラステクスチャーを描画する際にRect の変数を .uv() に渡すと、
/// ピクセルではなく割合（0.0〜1.0）として誤認識されてしまう可能性があるため
/// 今後描画する際は(Rect{})で代用してください。
/// 
/// </remarks>
void BattleUI::draw() const
{
	/// ステータス ///
	
		// プレイヤーのHp
		FontAsset(U"HUD")(U"{}"_fmt(m_battleSystem->GetCurrentPlayerHp()))
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 50, Vec2{ 600, 400 });
		// 空白の体力ゲージ
		TextureAsset(U"EmptyHealthbar").draw(500.0, 650.0);
		// 満タン状態の体力ゲージ
		TextureAsset(U"FullHealthbar")(Rect{0,0,playerHealthPct,10}).draw(510.0, 650.0);

		// エネミーのHp
		FontAsset(U"HUD")(U"{}"_fmt(0))
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 18, Vec2{ 1200, 400 });
		// 空白の体力ゲージ
		TextureAsset(U"EmptyHealthbar").draw(1300.0, 650.0);
		// 満タン状態の体力ゲージ
		TextureAsset(U"FullHealthbar")(Rect{ 0,0, enemyHealthPct,10 }).draw(1310.0, 650.0);
	

	/// コマンドウィンドウ ///
	{
		// コマンドウィンドウ
		TextureAsset(U"CommandWindow").drawAt(m_commandWindowPos);
		// カーソル
		Triangle(m_movedFirstPos, m_movedSecondPos, m_movedThirdPos).draw(Palette::White);

		// コマンド名
		FontAsset(U"Command")(U"攻撃")
			.draw(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), Vec2{ m_commandWindowPos.x - 70, m_commandWindowPos.y - 64 });
		FontAsset(U"Command")(U"防御")
			.draw(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), Vec2{ m_commandWindowPos.x - 70, m_commandWindowPos.y - 34 });
		FontAsset(U"Command")(U"スキル")
			.draw(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), Vec2{ m_commandWindowPos.x - 70, m_commandWindowPos.y });

		if (m_battleSystem->GetIsSkillMenu())
		{
			TextureAsset(U"SubCommandWindow").drawAt(m_subCommandWindowPos);
			Triangle(m_subMovedFirstPos, m_subMovedSecondPos, m_subMovedThirdPos).draw(Palette::White);
		}
	}

	/// デバッグ確認用 ///
	FontAsset(U"BattleSystem")(U"{}"_fmt(m_currentCommandIndex))
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 300 });
}

void BattleUI::SetReference(BattleSystem& battleSystem, Player* player)
{
	m_battleSystem = &battleSystem;
	m_player = player;
}

void BattleUI::UpdateCursorPos()
{
	m_currentCommandIndex = m_battleSystem->GetCommandIndex();
	//commandIndexによってカーソルの座標を移動させる
	m_offsetCursorY = { 32.0 * m_currentCommandIndex };
	m_movedFirstPos = m_cursorFirstPos.movedBy(0, m_offsetCursorY);
	m_movedSecondPos = m_cursorSecondPos.movedBy(0, m_offsetCursorY);
	m_movedThirdPos = m_cursorThirdPos.movedBy(0, m_offsetCursorY);
}

void BattleUI::UpdateSubCursorPos()
{
	m_currentCommandIndex = m_battleSystem->GetCommandIndex();
	//commandIndexによってカーソルの座標を移動させる
	m_subOffsetCursorY = { 32.0 * m_currentCommandIndex };
	m_subMovedFirstPos = m_subCursorFirstPos.movedBy(0, m_subOffsetCursorY);
	m_subMovedSecondPos = m_subCursorSecondPos.movedBy(0, m_subOffsetCursorY);
	m_subMovedThirdPos = m_subCursorThirdPos.movedBy(0, m_subOffsetCursorY);
}

