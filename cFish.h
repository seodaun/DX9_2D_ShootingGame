#pragma once
#include "cEnemy.h"
class cBullet;
class cFish :
	public cEnemy
{
private:
	D3DXVECTOR2 m_playerpos;
	vector<cBullet*>& m_PlayerBullet;
	RECT m_rColl;
	RECT m_rEnemy;
	float m_speed;
public:
	cFish(const D3DXVECTOR2& pos, const D3DXVECTOR2& playerPos, const float speed);
	~cFish();
public:
	virtual void Update() override;

};

