#include "DXUT.h"
#include "cEnemy.h" 

cEnemy::cEnemy(const D3DXVECTOR2& pos,double size, int Hp)
	: m_pos(pos), m_Hp(Hp)
{
	m_size = 300;
}

cEnemy::~cEnemy()
{
}

void cEnemy::Render()
{ 
	 	
	switch (m_State) {
	case CHARACTER_STATE::eIDLE:	m_EnemyAni[eIDLE]->CenterRender(m_pos.x, m_pos.y, 1, 0);	break;
	case CHARACTER_STATE::eDAMAGE:	m_EnemyAni[eDAMAGE]->CenterRender(m_pos.x, m_pos.y, 1, 0);	break;
	case CHARACTER_STATE::eDIE:		m_EnemyAni[eDIE]->CenterRender(m_pos.x, m_pos.y, 1, 0);		break;
	}
	if (IsOutMap()) {
		m_dead = true; 
		GAMEMANAGER->getPlayer()->Damage(1);
	}
}
 
bool cEnemy::IsOutMap()
{
	return (m_pos.x + m_size < 0 );
}