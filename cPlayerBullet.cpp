#include "DXUT.h"
#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(const D3DXVECTOR2& pos, const D3DXVECTOR2& pos2, int speed)
	:cBullet(pos, 20, atan2f((pos.y - pos2.y), (pos.x - pos2.x)) * 180 / 3.1415f-180), beforePos(pos), afterPos(pos2)
{
	m_image = IMAGEMANAGER->FindImage("bullet_0");
	m_DamageEffect = new cAnimation("DamageEffect", 0.08f, false);
	m_bullet = new cAnimation("bullet", 0.08f, true);
	m_speed = speed;
	bSuccession = false;
}
cPlayerBullet::cPlayerBullet(const D3DXVECTOR2& pos, const D3DXVECTOR2& pos2, int speed, float angle)
	: cBullet(pos, 20,angle-90), beforePos(pos), afterPos(pos2), m_angler(angle-90)
{
	m_image = IMAGEMANAGER->FindImage("bullet_0");
	m_DamageEffect = new cAnimation("DamageEffect", 0.08f, false);
	m_bullet = new cAnimation("bullet", 0.08f, true);
	m_speed = speed;
	bSuccession = true;
}
cPlayerBullet::~cPlayerBullet()
{ 
	SAFE_DELETE(m_DamageEffect);
	SAFE_DELETE(m_bullet);
}


void cPlayerBullet::Update()
{
	m_bullet->Update();
	if (m_die)
		m_state = DIE;
	else {
		if (!bSuccession) {
			D3DXVECTOR2 tpos;
			D3DXVECTOR2 Dis = afterPos - beforePos;
			D3DXVec2Normalize(&tpos, &Dis);
			m_pos.x += tpos.x * (300 + m_speed * 100) * DXUTGetElapsedTime();
			m_pos.y += tpos.y * (300 + m_speed * 100) * DXUTGetElapsedTime();
		}
		else {
			m_pos.x += cosf(3.141592 / 180 * m_angler) * (300 + m_speed * 100) * DXUTGetElapsedTime();
			m_pos.y += sinf(3.141592 / 180 * m_angler) * (300 + m_speed * 100) * DXUTGetElapsedTime();
		}
	}
	switch (m_state) {
	case BULLET_STATE::IDLE: {break; }
	case BULLET_STATE::DIE: { if (m_DamageEffect->Update()) isDead() = true;  break; }
	} 
}