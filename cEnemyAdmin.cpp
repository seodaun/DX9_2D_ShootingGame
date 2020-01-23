#include "DXUT.h"
#include "cEnemyAdmin.h"
#include "cEnemy.h"
#include "cBullet.h"  

#define COLLRANGE_X 300
#define COLLRANGE_Y WINSIZEY

cEnemyAdmin::cEnemyAdmin() 
{
	cntDeadEnemy = 0;
}

cEnemyAdmin::~cEnemyAdmin()
{
	for (auto iter : m_Enemy)
	{
		SAFE_DELETE(iter);
	}
	m_Enemy.clear();
} 
void cEnemyAdmin::Update()
{
	srand(time(NULL));
	for (auto iter = m_Enemy.begin(); iter != m_Enemy.end();) 
	{
		int r = rand() % 10;
		(*iter)->Update(); 
		if ((*iter)->isDead() == true) {
			if (r <= 3) GAMEMANAGER->earnMoney(r);
			FMOD.PlayEF("Death");
			SAFE_DELETE(*iter);
			iter = m_Enemy.erase(iter);
		}   
		else iter++;
	}
} 
void cEnemyAdmin::Render()
{
	for (auto iter : m_Enemy) iter->Render(); 
} 
