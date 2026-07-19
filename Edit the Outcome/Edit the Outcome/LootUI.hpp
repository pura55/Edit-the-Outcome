#pragma once
#include <Siv3D.hpp>

// 前方宣言
class LootSystem;

class LootUI
{
public:
	LootUI();
	void update();
	void draw() const;

	void SetReference(LootSystem& lootSytem);

	/// @brief 選択のカーソルの座標を更新する関数
	void UpdateSelectCursor();

	/// @brief 確認のカーソルの座標を更新する関数
	void UpdateCheckCursor();

private:
	Vec2 m_dwarfPos{ 200.0, 600.0 };       // ドワーフのアイコンの座標
	Vec2 m_speechFramePos{ 225.0, 550.0 }; // ドワーフのテキストの座標

	Vec2 m_itemFramePos{ 330.0, 350.0 }; // ルートアイテムを表示するフレームの座標

	Vec2 m_checkFramePos{ Scene::Center() }; // 獲得確認用のフレームの座標
	Vec2 m_checkButtonPos{ 570.0 , 370.0 }; // 獲得確認用のボタンの座標

#pragma region Cursor

	const Vec2 m_selectCursorPos{ m_itemFramePos.x , 470.0 }; // ルートアイテムを選択するカーソルの座標
	Vec2 m_movedSelectPos{ m_selectCursorPos };           // 移動後の選択用のカーソルの座標
	double m_offsetSelectCursorX{ 0 };                    // 選択用のカーソルの変更値

	int32 m_currentSelectIndex{ 0 }; // 現在の選択指数

	const Vec2 m_checkCursorPos{ 590.0 , 400.0 };  // 確認用のカーソルの座標
	Vec2 m_movedCheckPos{ m_selectCursorPos };            // 移動後の確認用のカーソルの座標
	double m_offsetCheckCursorX{ 0 };                     // 確認用のカーソルの変更値
	
	int32 m_currentCheckIndex{ 0 };  // 現在の確認指数

	double m_cosWave{ 0 }; // カーソルを動かすcos波
#pragma endregion

	LootSystem* m_lootSystem{ nullptr }; // ルートシステムの参照
};
