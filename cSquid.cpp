#include "DXUT.h"
#include "cSquid.h"
#include "cEnemyBullet.h"
#include "cBullet.h"
#include <string> 
cSquid::cSquid(const D3DXVECTOR2& pos, const D3DXVECTOR2& playerPos,const float speed)
	: cEnemy(pos, 300, 1), m_playerpos(playerPos), m_PlayerBullet(GAMEMANAGER->getPBulletAd()->GetPBullet())
{
	m_image = IMAGEMANAGER->FindImage("IdleSquid_0");
	m_speed = speed;
	m_EnemyAni[eIDLE] = new cAnimation("IdleSquid" ,0.08f, true); 
	m_EnemyAni[eDAMAGE] = new cAnimation("DamageSquid" ,0.08f, true); 
	m_EnemyAni[eDIE] = new cAnimation("DieSquid", 0.08f, false);
	m_State = eIDLE;

	m_rColl = { 0,0,(LONG)m_image->info.Width / 2,(LONG)m_image->info.Height / 2 };
}

cSquid::~cSquid()
{
	for (int j = 0; j < STATE_KIND; j++) SAFE_DELETE(m_EnemyAni[j]);
}

void cSquid::Update()
{
	if (m_State != eDIE)m_pos.x -= 100 * DXUTGetElapsedTime()*m_speed;
	switch (m_State) {
	case CHARACTER_STATE::eIDLE:	if (m_EnemyAni[eIDLE]->Update())	m_State = eIDLE;	break; 
	case CHARACTER_STATE::eDIE:		if (m_EnemyAni[eDIE]->Update())		m_dead = true;	break;
	}
	m_rEnemy = {
	(LONG)(m_pos.x - m_image->info.Width  / 2 +150),
	(LONG)(m_pos.y - m_image->info.Height / 2 ),
	(LONG)(m_pos.x + m_image->info.Width / 2 -100),
	(LONG)(m_pos.y + m_image->info.Height / 2 ) };
	for (auto iter = m_PlayerBullet.begin(); iter != m_PlayerBullet.end();) {
		RECT rPBullet = {
			(LONG)(*iter)->m_pos.x - (*iter)->m_image->info.Width / 2,
			(LONG)(*iter)->m_pos.y - (*iter)->m_image->info.Height / 2,
			(LONG)(*iter)->m_pos.x + (*iter)->m_image->info.Width / 2,
			(LONG)(*iter)->m_pos.y + (*iter)->m_image->info.Height / 2
		};
		if (IntersectRect(&m_rColl, &m_rEnemy, &rPBullet)) {
			if (!(*iter)->m_die) Damage();
			(*iter)->m_die = true;
		}
		iter++;
	}
}
