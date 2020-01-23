#pragma once
#include "cEnemy.h"
class cBullet;
class cAnglerfish :
	public cEnemy
{
private: 
	D3DXVECTOR2 m_playerpos;
	vector<cBullet*>& m_PlayerBullet;
	RECT m_rEnemy;
	RECT m_rColl;
	float m_speed;
public:
	cAnglerfish(const D3DXVECTOR2& pos, const D3DXVECTOR2& playerPos,const float speed);
	~cAnglerfish();
public:
	virtual void Update() override;

};

