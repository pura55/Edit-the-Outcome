#pragma once
#include <Siv3D.hpp>

class Enemy
{
public:
	/// HP ///

	/// @brief エネミーのHpを取得する関数
	int32 GetEnemyHp() { return m_enemyHp; }
	/// @brief エネミーのhpを設定する関数
	void SetEnemyHp(int32 hp) { m_enemyHp = hp; }

private:
	int32 m_enemyHp{ 5 };  //エネミーのHP
};
