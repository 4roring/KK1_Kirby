#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::ApplyDamage(int iDamage)
{
	CActor::ApplyDamage(iDamage);
}

void CEnemy::isDamage()
{
	float fAccX = m_bFlipX ? -0.7f : 0.7f;

	m_fVelocityX += fAccX;

	if (abs(m_fVelocityX) > 8.f)
	{
		m_bIsDamage = false;

		if (m_iHp <= 0)
			m_bActive = false;
	}
}

void CEnemy::isInhail()
{
	if (m_pTarget == nullptr)
		m_pTarget = GameManager->GetPlayer();

	float fAngle = CMath::DistanceAngle(this, m_pTarget);


	m_fVelocityX += 0.2f;

	m_tInfo.fX += cosf(fAngle) * m_fVelocityX;
	m_tInfo.fY -= sinf(fAngle) * m_fVelocityX;
}
