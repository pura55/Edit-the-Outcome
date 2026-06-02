#pragma once
#include <Siv3D.hpp>

class Player
{
public:

	/// HP ///
	
	/// @brief プレイヤーのHpを取得する関数
	int32 GetPlayerHp() { return m_playerHp; }
	/// @brief プレイヤーのhpを設定する関数
	void SetPlayerHp(int32 hp) { m_playerHp = hp; }

	/// ATK ///
	
	/// @brief プレイヤーのAtkを取得す関数
	int32 GetPlayerAtk() { return m_playerAtk; }
	/// @brief プレイヤーのAtkを設定する関数
	void SetPlayerAtk(int32 atk) { m_playerAtk = atk; }
    
private:
	int32 m_playerHp{10};  //プレイヤーのHP
	int32 m_playerAtk{1};  //プレイヤーの攻撃力
};
