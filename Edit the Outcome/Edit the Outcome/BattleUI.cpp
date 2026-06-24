#include "stdafx.h"
#include "BattleUI.hpp"
#include "BattleSystem.hpp"
#include "CommandManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

BattleUI::BattleUI() :m_player{ nullptr }
{
}

void BattleUI::update(CommandManager& commandManager)
{
	if (not commandManager.GetIsSkillWindow())
	{
		// カーソルを更新
		UpdateCursorPos();
	}
	else
	{
		// サブのカーソルを更新
		UpdateSubCursorPos();
	}
}

/// <remarks>
/// 描画に関する注意点を記述します。
///
/// アトラステクスチャーを描画する際にRect の変数を .uv() に渡すと、
/// ピクセルではなく割合（0.0〜1.0）として誤認識されてしまう可能性があるため
/// 今後描画する際は(Rect{})で代用してください。
/// 
/// </remarks>
void BattleUI::draw(CommandManager& commandManager) const
{
	/// ステータス ///
	{
		// プレイヤーのHp
		FontAsset(U"HUD")(U"{}"_fmt(m_player->GetCurrentPlayerHp()))
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 50, Vec2{ 600, 400 });
		// 空白の体力ゲージ
		TextureAsset(U"EmptyHealthbar").draw(500.0, 650.0);
		// 緑色の体力ゲージ
		TextureAsset(U"FullHealthbar")(Rect{ 0,0,m_player->CalculatePctOfHp(),10 }).draw(510.0, 650.0);

		for (auto* enemies : m_enemies)
		{
			// エネミーのHp
			FontAsset(U"HUD")(U"{}"_fmt(enemies->GetEnemyHp())).drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 18, Vec2{ 1200, 400 });
			// 空白の体力ゲージ
			TextureAsset(U"EmptyHealthbar").draw(1100.0 + 200.0 * enemies->GetGenerateNum(), 650.0);
			// 緑色の体力ゲージ
			TextureAsset(U"FullHealthbar")(Rect{ 0,0, enemies->CalculatePctOfHp(),10 }).draw(1110.0 + 200.0 * enemies->GetGenerateNum(), 650.0);
		}
	}
	

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
			.draw(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), Vec2{ m_commandWindowPos.x - 70, m_commandWindowPos.y - 32 });
		FontAsset(U"Command")(U"スキル")
			.draw(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), Vec2{ m_commandWindowPos.x - 70, m_commandWindowPos.y });

		if (commandManager.GetIsSkillWindow())
		{
			TextureAsset(U"SubCommandWindow").drawAt(m_subCommandWindowPos);
			Triangle(m_subMovedFirstPos, m_subMovedSecondPos, m_subMovedThirdPos).draw(Palette::White);

			std::vector<String> commandName = commandManager.GetCommandName();

			for (size_t i = 0; i < commandName.size(); i++)
			{
				// 移動量
				int offsetX = 1;
				int offsetY = 0;

				// 要素が5以上の時、各軸を移動
				// x軸の処理
				i >= 4 ? offsetX = 0 : offsetX = 1;
				// y軸の処理
				offsetY = i % 4;

				FontAsset(U"Command")(commandName[i])
					.draw(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), Vec2{ m_subCommandWindowPos.x - 200 * offsetX, m_subCommandWindowPos.y - 64 + (32 * offsetY) });
				
			}
		}
	}

	/// デバッグ確認用 ///
	FontAsset(U"BattleSystem")(U"{}"_fmt(m_currentCommandIndex))
		.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 300 });
}

void BattleUI::SetReference(BattleSystem& battleSystem, Player* player, std::vector<Enemy*> enemy)
{
	m_battleSystem = &battleSystem;
	m_player = player;
	m_enemies = enemy;
}

void BattleUI::UpdateCursorPos()
{
	m_currentCommandIndex = m_battleSystem->GetCommandIndex();

	//commandIndexによってカーソルの座標を移動させる
	m_offsetCursorY = ( 32.0 * m_currentCommandIndex);
	m_movedFirstPos = m_cursorFirstPos.movedBy(0, m_offsetCursorY);
	m_movedSecondPos = m_cursorSecondPos.movedBy(0, m_offsetCursorY);
	m_movedThirdPos = m_cursorThirdPos.movedBy(0, m_offsetCursorY);
}

void BattleUI::UpdateSubCursorPos()
{
	m_currentCommandIndex = m_battleSystem->GetCommandIndex();

	// indexが4以上の場合x軸をずらす
	m_currentCommandIndex >= 4 ? m_subOffsetCursorX = 200.0 : m_subOffsetCursorX = 0.0;
	
	// コマンドウィンドウのサイズが5行以上でy軸がはみ出すため
	// indexが4以上の時は余りの数で座標を調整する
	m_currentCommandIndex = m_currentCommandIndex % 4;
	m_subOffsetCursorY = ( 32.0 * m_currentCommandIndex );

	m_subMovedFirstPos = m_subCursorFirstPos.movedBy(m_subOffsetCursorX, m_subOffsetCursorY);
	m_subMovedSecondPos = m_subCursorSecondPos.movedBy(m_subOffsetCursorX, m_subOffsetCursorY);
	m_subMovedThirdPos = m_subCursorThirdPos.movedBy(m_subOffsetCursorX, m_subOffsetCursorY);
}

