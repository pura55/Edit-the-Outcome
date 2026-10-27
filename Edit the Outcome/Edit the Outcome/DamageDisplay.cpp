#include "stdafx.h"
#include "DamageDisplay.hpp"

DamageDisplay::DamageDisplay()
{
	ResetLeftTime();
}

void DamageDisplay::update()
{
	MovePosition();
}

void DamageDisplay::draw() const
{
	m_fontBackDamage(U"{}"_fmt(m_showDamage)).drawAt(m_targetPosition, Palette::White);
	m_fontDamage(U"{}"_fmt(m_showDamage)).drawAt(m_targetPosition, Palette::Red);
}

void DamageDisplay::MovePosition()
{
	m_targetPosition.x += m_moveVelocity * Scene::DeltaTime();
	m_targetPosition.y -= m_moveVelocity * Scene::DeltaTime();
}
