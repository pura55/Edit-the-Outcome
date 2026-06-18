#include "stdafx.h"
#include "GlobalData.hpp"

GlobalData::GlobalData()
{
}

void GlobalData::update()
{

}

void GlobalData::init()
{
	imageLoader.init();
}

bool GlobalData::LoadAllData()
{
	// 各データの読み込みに失敗した場合falseを返します
	if (not LoadPlayerData()) return false;
	if (not LoadEnemyData()) return false;
	if (not LoadCommandData()) return false;

	// 初期値のプレイヤーデータを進捗用データにコピーします
	m_playerProgress = m_playerMasterTable;

	// 初期値のコマンドデータを進捗用データにコピーします
	m_commandProgress = m_commandMasterTable;
	
	// データの読み込みに成功した場合trueを返します
	return true;
}

bool GlobalData::LoadPlayerData()
{
	const JSON json = JSON::Load(U"./json/player_data.json");

	//jsonファイル読み込み確認用コード
	//if (json)
	//{
	//	// 読み込んだJSONの構造をインデント付きの綺麗なテキストにしてコンソールに吐き出す
	//	Console << U"--- 読み込み成功したJSONの中身 ---";
	//	Console << json.format();
	//	Console << U"----------------------------------";
	//}

	// データがない場合falseで返します
	if (not json) return false;

	// jsonファイルを確認し各要素をマスターテーブルに登録します
	// [注釈]：型が複数存在するためautoを使用しエラーを防止
	for (const auto& playerJson : json[U"players"].arrayView())
	{
		PlayerProgressData d;
		d.id = playerJson[U"id"].get<int32>();
		d.name = playerJson[U"name"].get<String>();
		d.maxHp = playerJson[U"hp"].get<int32>();
		d.atk = playerJson[U"atk"].get<int32>();

		m_playerMasterTable.push_back(d);
	}

	// 登録が完了した場合trueで返します
	return true;
}

const PlayerProgressData& GlobalData::GetPlayerData(int32 id) const
{
	// 一致するidを検索して返します
	for (const auto& data : m_playerMasterTable)
	{
		if (data.id == id) return data;
	}

	// 見つからない場合はダミーエラーを返します
	return m_playerMasterTable[0];
}

bool GlobalData::LoadEnemyData()
{
	// jsonファイルを読み込みます
	const JSON json = JSON::Load(U"./json/enemy_data.json");

	// データがない場合falseで返します
	if (not json) return false;

	// jsonファイルを確認し各要素をマスターテーブルに登録します
	// [注釈]：型が複数存在するためautoを使用しエラーを防止
	for (const auto& enemyJson : json[U"enemies"].arrayView())
	{
		EnemyData d;
		d.id = enemyJson[U"id"].get<int32>();
		d.name = enemyJson[U"name"].get<String>();
		d.maxHp = enemyJson[U"hp"].get<int32>();
		d.atk = enemyJson[U"atk"].get<int32>();

		m_enemyMasterTable.push_back(d);
	}

	// 登録が完了した場合trueで返します
	return true;
}

const EnemyData& GlobalData::GetEnemyData(int32 id) const
{
	// 一致するidを検索して返します
	for (const auto& data : m_enemyMasterTable)
	{
		if (data.id == id) return data;
	}

	// 見つからない場合はダミーエラーを返します
	return m_enemyMasterTable[0];
}

bool GlobalData::LoadCommandData()
{
	// jsonファイルを読み込みます
	const JSON json = JSON::Load(U"./json/command_data.json");

	// データがない場合falseで返します
	if (not json) return false;

	// jsonファイルを確認し各要素をマスターテーブルに登録します
	// [注釈]：型が複数存在するためautoを使用しエラーを防止
	for (const auto& commandJson : json[U"commands"].arrayView())
	{
		CommandData d;
		d.id = commandJson[U"id"].get<int32>();
		d.name = commandJson[U"name"].get<String>();
		d.dmg = commandJson[U"dmg"].get<int32>();

		m_commandMasterTable.push_back(d);
	}

	// 登録が完了した場合trueで返します
	return true;
}

const CommandData& GlobalData::GetCommandData(int32 id) const
{
	// 一致するidを検索して返します
	for (const auto& data : m_commandMasterTable)
	{
		if (data.id == id) return data;
	}

	// 見つからない場合はダミーエラーを返します
	return m_commandMasterTable[0];
}
