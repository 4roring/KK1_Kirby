#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
	m_ewKnockBackTimer = GetTickCount();
}


CEnemy::~CEnemy()
{
}

void CEnemy::ApplyDamage(int iDamage)
{
	if (!m_bIsDamage)
	{
		CActor::ApplyDamage(iDamage);
		m_ewKnockBackTimer = GetTickCount() + 300;
		m_bIsDamage = true;
	}
}

void CEnemy::isDamage()
{
	float m_fVelocityX = m_bFlipX ? -4.f : 4.f;

	m_tInfo.fX += m_fVelocityX;

	if (m_ewKnockBackTimer < GetTickCount())
		m_bIsDamage = false;
}

void CEnemy::isInhail()
{
	if (m_pTarget == nullptr)
		m_pTarget = GameManager->GetPlayer();

	float fAngle = CMath::DistanceAngle(this, m_pTarget);

	m_fVelocityX += 0.5f;

	m_tInfo.fX += cosf(fAngle) * m_fVelocityX;
	m_tInfo.fY -= sinf(fAngle) * m_fVelocityX;

	if (m_bIsDamage)
	{
		m_bIsDamage = false;
		m_bActive = false;
	}
}
