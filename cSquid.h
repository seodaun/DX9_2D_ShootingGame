#pragma once
#include "cEnemy.h"
class cBullet;
class cSquid :
	public cEnemy
{
private:
	D3DXVECTOR2 m_playerpos;
	vector<cBullet*>& m_PlayerBullet;
	RECT m_rEnemy;
	RECT m_rColl;
	float m_speed;
public:
	cSquid(const D3DXVECTOR2& pos, const D3DXVECTOR2& playerPos, const float speed);
	~cSquid();
public:
	virtual void Update() override;

};

