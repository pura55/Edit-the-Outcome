#pragma once
#include "ImageLoader.hpp"
#include "PlayerProgressData.hpp"
#include "EnemyData.hpp"
#include "CommandData.hpp"
#include "RandomEngine.hpp"

/// <summary>
/// グローバルデータ
///
/// ゲーム全体で共有するデータを管理するクラス
/// </summary>
class GlobalData
{
	/// <summary>
	/// public関数
	/// </summary>
public:
	/// @brief シード値をランダムエンジンに渡す
	GlobalData():m_randomEngine(m_rngSeed){};

	/// @brief 初期化をする関数
	void init();

	/// @brief 全てのデータをロードする関数
	bool LoadAllData();

	/// @brief プレイヤーのデータをロードする関数
	bool LoadPlayerData();

	/// @brief idを指定して、プレイヤーのデータを取得する関数
	const PlayerProgressData& GetPlayerData(int32 id) const;

	/// @brief エネミーのデータをロードする関数
	bool LoadEnemyData();

    /// @brief idを指定して、特定のエネミーのデータを取得する関数
	const EnemyData& GetEnemyData(int32 id) const;

	/// @brief コマンドのデータをロードすdる関数 
	bool LoadCommandData();

	/// @brief  idを指定して、コマンドのデータを取得する関数
	const CommandData& GetCommandData(int32 id) const;

public:
	// イメージローダーを保持
	ImageLoader imageLoader;

	// ランダムエンジンを保持
	RandomEngine m_randomEngine;

	// プレイヤーの進捗データを保持(変更可能)
	std::vector<PlayerProgressData> m_playerProgress;

	// プレイヤーの初期データを保持(変更不可)
	std::vector<PlayerProgressData> m_playerMasterTable;

	// エネミーのデータを保持(変更不可)
	std::vector<EnemyData> m_enemyMasterTable;

	// コマンドの進捗データを保持(変更可能)
	std::vector<CommandData> m_commandProgress;

	// コマンドのデータを保持(変更不可)
	std::vector<CommandData> m_commandMasterTable;

	// 現在選択されているキャラクターID
	int32 m_currentCharacterID{1};

	// ランダム変数を生成するためのシード値
	const uint32 m_rngSeed{ 1234567 }; 
};
