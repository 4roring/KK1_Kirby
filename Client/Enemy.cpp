#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Initialize()
{
}

void CEnemy::LateInit()
{
}

OBJ_STATE CEnemy::Update()
{
	return OBJ_STATE();
}

void CEnemy::LateUpdate()
{
}

void CEnemy::Render(HDC hDC)
{
}

void CEnemy::Release()
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

		std::cout << m_bActive << std::endl;
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
