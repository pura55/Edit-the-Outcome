#pragma once
#include "Siv3D.hpp"
#include "CutTime.hpp"

/// <summary>
/// ダメージディスプレイ
///
/// ダメージを表示するクラス
/// </summary>
class DamageDisplay : public CutTime
{
public:
	DamageDisplay();
	void update();
	void draw() const;

	/// @brief 情報を渡す関数
	/// @param damage 与えるダメージ
	/// @param position 対象の座標
	void SetInformation(int32 damage, Vec2 position)
	{
		m_showDamge = damage;
		m_targetPosition = position;
	}

	/// @param skillNums スキルの回数
	void SetInformation(int32 damage, Vec2 position, int32 skillNums)
	{
		m_showDamge = damage;
		m_targetPosition.x = position.x + skillNums * 5.0;
		m_targetPosition.y = position.y + skillNums * 5.0;
	}

	/// @brief 表示時間をリセットする関数
	void ResetLeftTime() { m_leftTime = m_showTime; }

	/// @brief ダメージ表示フラグを返す関数
	bool GetIsShow() { return isShowDamage; }

	/// @brief ダメージ表示フラグを設定する関数
	/// @param show 設定するフラグ
	void SetIsShow(bool show) { isShowDamage = show; }

private:
	/// @brief 座標を移動させる関数
	void MovePosition();

private:
	Font m_fontBackDamage{ FontMethod::MSDF, 18, Typeface::Bold };// ダメージの背景
	Font m_fontDamage{ FontMethod::MSDF, 16, Typeface::Bold }; // ダメージのフォント

	int32 m_showDamge{ 0 }; // 表示するダメージ

	Vec2 m_targetPosition{ 0,0 }; // ダメージを表示する座標

	double m_showTime{ 1.0 }; // 表示時間

	double m_moveVelocity{ 20.0 }; // 移動する速度

	bool isShowDamage{ false }; // ダメージを表示するフラグ
};
