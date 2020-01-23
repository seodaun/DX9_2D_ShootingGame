#include "DXUT.h"
#include "cBullet.h"  
cBullet::cBullet(const D3DXVECTOR2& pos, double size, float degree)
	:m_size(size), m_degree(degree)
{ 
	bCollMouse = false;
	m_pos.x = pos.x;
	m_pos.y = pos.y; 
}


cBullet::~cBullet()
{  
}

void cBullet::Render()
{ 
	 switch (m_state) {
	 case BULLET_STATE::IDLE:  m_bullet->CenterRender(m_pos.x, m_pos.y, 1, m_degree );   break;
	 case BULLET_STATE::DIE:   m_DamageEffect->CenterRender(m_pos.x, m_pos.y, 1, 0); break;
	 }
}

bool cBullet::IsOutMap()
{
	return (m_pos.x - m_size < 0
		|| m_pos.x + m_size > WINSIZEX
		|| m_pos.y - m_size < 0
		|| m_pos.y + m_size > WINSIZEY);
}
