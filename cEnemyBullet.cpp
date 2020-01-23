#include "DXUT.h"
#include "cEnemyBullet.h"

cEnemyBullet::cEnemyBullet(const D3DXVECTOR2& enemyPos,const D3DXVECTOR2& playerPos)
	:cBullet(enemyPos, 20, 180),pos(enemyPos),targetPos(playerPos)
{
	m_image = IMAGEMANAGER->FindImage("bullet_0");
	m_bullet = new cAnimation("bullet", 0.08f, true);
}

cEnemyBullet::~cEnemyBullet()
{
	SAFE_DELETE(m_bullet);
}

void cEnemyBullet::Update()
{
	m_bullet->Update();
	D3DXVECTOR2 tpos;
	D3DXVECTOR2 Dis = pos - targetPos;
	D3DXVec2Normalize(&tpos, &Dis);
	if (!bCollMouse) {
		m_pos.x -= 300 * DXUTGetElapsedTime()*tpos.x;
		m_pos.y -= 300 * DXUTGetElapsedTime()*tpos.y;
	}
}