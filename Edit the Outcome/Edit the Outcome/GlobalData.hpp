#pragma once
#include "ImageLoader.hpp"
#include "PlayerProgressData.hpp"
#include "EnemyData.hpp"
#include "CommandData.hpp"

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
	GlobalData();
	void update();
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

	/// @brief コマンドのデータをロードする関数 
	bool LoadCommandData();

	/// @brief  idを指定して、コマンドのデータを取得する関数
	const CommandData& GetCommandData(int32 id) const;

public:
	/// データを保持 ///
	ImageLoader imageLoader;

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
	int32 currentCharacterID{1};
};
