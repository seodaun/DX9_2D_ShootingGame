#include "DXUT.h"
#include "cAnglerfish.h"
#include "cEnemyBullet.h"
#include "cBullet.h"
#include "cFps.h"
cAnglerfish::cAnglerfish(const D3DXVECTOR2& pos,const D3DXVECTOR2& playerPos)
	: cEnemy(pos,300, 2), m_playerpos(playerPos)
{ 
	m_image = IMAGEMANAGER->FindImage("Enemy_1");
	time = new cFps;
	time->SetStartTime();
}

cAnglerfish::~cAnglerfish()
{
	SAFE_DELETE(time);
}

void cAnglerfish::Update()
{ 
	m_pos.x -= 100 * DXUTGetElapsedTime();  
}
