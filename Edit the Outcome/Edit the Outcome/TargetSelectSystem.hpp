#pragma once
#include "Selector.hpp"

class Player;
class Enemy;

/// <summary>
/// ターゲットセレクトシステム
///
/// 敵を選択する処理を行うクラス
/// </summary>
class TargetSelectSystem : Selector
{
public:
	TargetSelectSystem();

	/// @brief 参照を登録する関数
	void SetReference(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies);

	/// @brief 攻撃するターゲットを選択する関数
	void TargetSelect();

	/// @brief 攻撃するターゲットを選択する関数(スキルver)
	void TargetSelect(int32 skillID);

	/// @brief 死亡している敵を除外する関数
	void ExclusionEnemies();

	/// @brief 敵の最大数を取得する関数
	int32 GetMaxNum() const{ return m_maxEnemiesNum; }

	/// @brief 選択しているターゲットを取得する関数
	int32 GetSelectTarget() const { return m_targetSelectIndex; }

	/// @brief 選択フラグを返す関数
	bool GetIsTargetSelected() const { return m_isTargetSelected; }

	/// @brief 選択フラグを設定する関数
	void SetIsTargetSelected(bool select) { m_isTargetSelected = select; }

private:
	/// @brief 敵の除外設定の初期化
	void InitExclusionEnemies();

private:

	int32 m_maxEnemiesNum{ 0 }; // エネミーの最大数（死んでいた場合繰りさげで最大を入れ替える）

	int32 m_minEnemiesNum{ 0 }; // エネミーの最小数（死んでいた場合繰り上げで最小を入れ替える）

	int32 m_targetSelectIndex{ 0 }; // 選択しているターゲットの指数

	bool m_isTargetSelected{ false }; // 選択フラグ

	std::vector<int32> m_exclusionEnemiesNum; // 除外する敵の番号

	Player* m_player{ nullptr }; // プレイヤーの参照

	std::vector<std::unique_ptr<Enemy>>* m_enemies; // エネミーの参照
	
};
