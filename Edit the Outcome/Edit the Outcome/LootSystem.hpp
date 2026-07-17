#pragma once
#include <Siv3D.hpp>
#include "CommandData.hpp"
#include "PlayerProgressData.hpp"

enum LootState
{
	Init,      // 初期化
	Selecting, // 選択
	Finished   // 終了
};

/// <summry>

class LootSystem
{
public:
	LootSystem();
	void update();

	// ルートに関わるデータを格納する関数
	void SetLootData(std::vector<CommandData>& commandData, std::vector<PlayerProgressData>& playerData);

	// 初期化の処理を行う関数
	void LootInit();

	// ルートアイテム選択状態の関数
	void LootSelecting();

	// ルートアイテム選択終了の処理を行う関数
	void LootFinished();

	// アイテムの種類を決定する関数
	void DecideKindOfItem();

	// アイテムを獲得する関数
	void AcquireItem();

	// アイテム獲得を確認する関数
	bool CheckAcquisition();

	// ルートアイテムを選択したかどうかのフラグを返す関数
	bool GetLootItemSelected() { return m_lootItemSelected; }

private:
	LootState m_lootState{ LootState::Init }; // ルートステート

	int32 m_maxSelectIndex{ 0 }; //選択指数の最大値

	int32 m_selectIndex{ 0 }; // 選択指数

	int32 m_maxCheckIndex{ 1 }; // 確認指数の最大値

	int32 m_checkIndex{ 0 }; // 確認指数

	bool m_lootItemSelected{ false }; // アイテムを選択したかどうかのフラグ

	bool m_needAcquireCheck{ false }; // アイテムを獲得するかどうかを確認するフラグ(true: 確認する, false: 確認しない）

	std::vector<CommandData> m_commandData; // コマンドデータ

	std::vector<PlayerProgressData> m_playerData; // プレイヤーデータ
};
