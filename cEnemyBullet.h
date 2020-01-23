#pragma once
#include "cBullet.h"
class cEnemyBullet : public cBullet
{
public:
	cEnemyBullet(const D3DXVECTOR2& enemyPos, const D3DXVECTOR2& playerPos);
	~cEnemyBullet();

	virtual void Update() override; 
private:
	D3DXVECTOR2 targetPos, pos; 
};

