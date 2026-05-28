#pragma once
#include <Siv3D.hpp>

// 前方宣言
class BattleSystem;
class ImageLoader;

/// <summary>
/// バトルUI
/// 
/// バトルでコマンド振動やHPバーなどのUIを表示するクラス
/// </summary>
class BattleUI
{
	/// <summary>
	/// 基本的な関数
	/// </summary>
public:
	BattleUI();
	void update();
	void draw() const;

	/// <summary>
	/// Setter/Getter
	/// </summary>
public:
	void SetReference(BattleSystem& battleSystem, ImageLoader& imageLoader);

	/// <summary>
	/// 機能関数
	/// </summary>
public:
	void UpdateCursorPos();
	void UpdateSubCursorPos();

	/// <summary>
	/// 一般型名変数
	/// </summary>
private:
	//コマンドインデックス
	int m_currentCommandIndex{ 0 };

	//シーンのサイズ
	double width{ 1920.0 };
	double height{ 1080.0 };


	///コマンドウィンドウ///


	//コマンドウィンドウの座標(画像サイズ256/192)
	const Vec2 m_commandWindowPos{ width * 0.25, height * 0.8 };
	//矢印の三点の基本座標
	const Vec2 m_cursorFirstPos{ m_commandWindowPos.x - 128.0 + 32.0, m_commandWindowPos.y - 96.0 + 32.0};
	const Vec2 m_cursorSecondPos{ m_commandWindowPos.x - 128.0 + 32.0, m_commandWindowPos.y - 96.0 + 48.0};
	const Vec2 m_cursorThirdPos{ m_commandWindowPos.x - 128.0 + 32.0 + 16.0, m_commandWindowPos.y - 96.0 + 40.0};
	//矢印の移動後の三点の基本座標
	Vec2 m_movedFirstPos{ 0, 0 };
	Vec2 m_movedSecondPos{ 0, 0 };
	Vec2 m_movedThirdPos{ 0, 0 };
	//矢印の変更値
	double m_offsetCursorY{ 0 };


	///サブコマンドウィンドウ///


	//コマンドウィンドウの座標(画像サイズ512/192)
	const Vec2 m_subCommandWindowPos{ m_commandWindowPos.x + 384.0, height * 0.8 };
	//矢印の三点の基本座標
	const Vec2 m_subCursorFirstPos{ m_subCommandWindowPos.x - 256.0 + 32.0, m_subCommandWindowPos.y - 96.0 + 32.0 };
	const Vec2 m_subCursorSecondPos{ m_subCommandWindowPos.x - 256.0 + 32.0, m_subCommandWindowPos.y - 96.0 + 48.0 };
	const Vec2 m_subCursorThirdPos{ m_subCommandWindowPos.x - 256.0 + 32.0 + 16.0, m_subCommandWindowPos.y - 96.0 + 40.0 };
	//矢印の移動後の三点の基本座標
	Vec2 m_subMovedFirstPos{ 0, 0 };
	Vec2 m_subMovedSecondPos{ 0, 0 };
	Vec2 m_subMovedThirdPos{ 0, 0 };
	//矢印の変更値
	double m_subOffsetCursorY{ 0 };

	//コマンド選択のハンドル
	bool m_isCommandDecide{ false };


	///ポインタの保持///


	//バトルシステムのポインタを保持
	BattleSystem* m_battleSystem{ nullptr };
	//イメージローダーのポインタを保持
	ImageLoader* m_imageLoader{ nullptr };
};
