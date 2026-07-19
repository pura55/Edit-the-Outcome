#pragma once
#include <Siv3D.hpp>
#include "CommandData.hpp"
#include "PlayerProgressData.hpp"

/// <summary>
/// ルートステート
///
/// ルートシステムの状態
/// </summary>
enum LootState
{
	Init,      // 初期化
	Selecting, // 選択
	Finished   // 終了
};

/// <summary>
/// メニューステート
///
/// 開いているメニューの状態
/// </summary>
enum LootMenuState
{
	Select, // 選択
	Check,  // 確認
	Finish  // 終了
};

/// <summary>
/// ルートシステム
///
/// ルートシーンの処理を行う関数
/// </summary>

class LootSystem
{
public:
	LootSystem();
	void update();

	/// @brief ルートに関わるデータを格納する関数
	void SetLootData(std::vector<CommandData>& commandData, std::vector<PlayerProgressData>& playerData);

	/// @brief 選択指数を返す関数
	int32 GetSelectIndex() const { return m_selectIndex; }

	/// @brief 確認指数を返す関数
	int32 GetCheckIndex() const { return m_checkIndex; }

	/// @brief メニューステートのスタックによって戻り値を変更
	int32 GetMenuState() const
	{
		switch (m_menuStack.top())
		{
		case LootMenuState::Select:
			return 0;
			
		case LootMenuState::Check:
			return 1;

		case LootMenuState::Finish:
			return 2;
		}
	}

	/// @brief ルートアイテムを選択したかどうかのフラグを返す関数
	bool GetLootItemSelected() { return m_lootItemSelected; }
private:
	/// @brief 初期化の処理を行う関数
	void LootInit();

	/// @brief ルートアイテム選択状態の関数
	void LootSelecting();

	/// @brief ルートアイテム選択終了の処理を行う関数
	void LootFinished();

	/// @brief アイテムの種類を決定する関数
	void DecideKindOfItem();

	/// @brief アイテムを獲得する関数
	void AcquireItem();

	/// @brief アイテム獲得を確認する関数
	bool CheckAcquisition();

private:
	LootState m_lootState{ LootState::Init }; // ルートステート

	int32 m_maxSelectIndex{ 2 }; //選択指数の最大値

	int32 m_selectIndex{ 0 }; // 選択指数

	int32 m_maxCheckIndex{ 1 }; // 確認指数の最大値

	int32 m_checkIndex{ 0 }; // 確認指数

	bool m_lootItemSelected{ false }; // アイテムを選択したかどうかのフラグ

	bool m_needAcquireCheck{ false }; // アイテムを獲得するかどうかを確認するフラグ(true: 確認する, false: 確認しない）

	std::stack<LootMenuState> m_menuStack; // メニューのスタック

	std::vector<CommandData> m_commandData; // コマンドデータ

	std::vector<PlayerProgressData> m_playerData; // プレイヤーデータ
};
