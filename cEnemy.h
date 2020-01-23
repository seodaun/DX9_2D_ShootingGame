#pragma once
class cEnemy abstract
{
protected:
	bool m_dead=false;
protected:
	double m_size;
	int m_Hp; 
public:
	texture* m_image;
	D3DXVECTOR2 m_pos;
	cAnimation* m_EnemyAni[STATE_KIND];
	CHARACTER_STATE m_State;
	cEnemy(const D3DXVECTOR2& pos, double size, int Hp);
	//가상 함수
	//자식클래스에서 재정의가 될 수도 있음
	virtual ~cEnemy();

	//순수 가상 함수
	//자식클래스가 정의 해줄꺼임
	virtual void Update() PURE;
	void Render();

	bool& isDead() { return m_dead; }
	bool IsOutMap();
	void SetHp(int hp) { m_Hp = hp; }
	int GetHp() { return m_Hp; }
	void Damage() {
		m_Hp--; 
		if (m_Hp <= 0) {
			m_State = eDIE;
			GAMEMANAGER->cntKill();
			DEBUG_LOG(GAMEMANAGER->getCntKill());
		}
	}
};

