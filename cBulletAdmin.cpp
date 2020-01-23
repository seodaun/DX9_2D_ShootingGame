#include "DXUT.h"
#include "cBulletAdmin.h" 
#include "cBullet.h"

cBulletAdmin::cBulletAdmin()
{ 
	m_bulletspeed = 300;
}


cBulletAdmin::~cBulletAdmin()
{
	Reset();
}

void cBulletAdmin::Reset()
{
	for (auto iter : m_PBullet)
		SAFE_DELETE(iter);
	m_PBullet.clear();
	for (auto iter : m_EBullet)
		SAFE_DELETE(iter);
	m_EBullet.clear();
}

void cBulletAdmin::Update()
{ 
	for (auto iter = m_PBullet.begin(); iter != m_PBullet.end();) {
		(*iter)->Update();   
		if ((*iter)->IsOutMap())(*iter)->isDead() = true; 
		if ((*iter)->isDead() == true) { 
			SAFE_DELETE(*iter);
			iter = m_PBullet.erase(iter);
		}
		else iter++;
	} 
	for (auto iter = m_EBullet.begin(); iter != m_EBullet.end();) {
		(*iter)->Update(); 
		if ((*iter)->IsOutMap())(*iter)->isDead() = true;
		if ((*iter)->isDead() == true) {
			SAFE_DELETE(*iter);
			iter = m_EBullet.erase(iter);
		}
		else iter++;
	}
}

void cBulletAdmin::Render()
{
	for (auto iter : m_PBullet)
		iter->Render();
	for (auto iter : m_EBullet)
		iter->Render();
	 
} 