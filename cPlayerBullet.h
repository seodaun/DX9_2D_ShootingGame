#pragma once
#include "cBullet.h"

class cPlayerBullet : public cBullet
{
public:
	cPlayerBullet(const D3DXVECTOR2& pos, const D3DXVECTOR2& pos2, int speed);
	cPlayerBullet(const D3DXVECTOR2& pos, const D3DXVECTOR2& pos2, int speed, float angle);
	~cPlayerBullet();

	virtual void Update() override;
private:
	D3DXVECTOR2 beforePos, afterPos;
	int m_speed; 
	bool bSuccession = false; // ¿¬¹ßÃÑ¾Ë
	float m_angler=0; 
};

