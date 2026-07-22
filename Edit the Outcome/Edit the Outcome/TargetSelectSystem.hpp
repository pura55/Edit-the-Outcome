#pragma once
#include <Siv3D.hpp>

class Player;
class Enemy;

/// <summary>
/// ターゲットセレクトシステム
///
/// 敵を選択する処理を行うクラス
/// </summary>
class TargetSelectSystem
{
public:
	TargetSelectSystem();

	/// @brief 参照を登録する関数
	void SetReference(Player* player, std::vector<Enemy*> enemies);

	/// @brief 攻撃するターゲットを選択する関数
	void TargetSelect(int32& selectIndex, bool& isSelected);

	/// @brief 死亡している敵を除外する関数
	void ExclusionEnemies(int32& selectIndex);

	/// @brief エネミーの数（最大値）を登録する関数
	void RegistMaxEnemiesNum() { m_maxEnemiesNum = m_enemies.size() - 1; }

private:
	/// @brief 敵の除外設定の初期化
	void InitExclusionEnemies();


private:

	int32 m_maxEnemiesNum{ 0 }; // エネミーの最大数（死んでいた場合繰りさげで最大を入れ替える）

	int32 m_minEnemiesNum{ 0 }; // エネミーの最小数（死んでいた場合繰り上げで最小を入れ替える）

	std::vector<int32> m_exclusionEnemiesNum; // 除外する敵の番号

	Player* m_player{ nullptr }; // プレイヤーの参照

	std::vector<Enemy*> m_enemies; // エネミーの参照
	
};
