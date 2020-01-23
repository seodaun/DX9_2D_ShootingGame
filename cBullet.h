#pragma once
class cBullet abstract
{
protected:
	double m_size; 
	BULLET_STATE m_state = IDLE;
public:
	texture* m_image;
	D3DXVECTOR2 m_pos;
	cAnimation* m_DamageEffect;
	cAnimation* m_bullet;
	bool m_die = false;
private:
	float m_degree;  
	bool m_dead = false;
protected:
	bool bCollMouse;//���콺�� �浹�ߴ��� Ȯ���ϴ� ����
public: 
	cBullet(const D3DXVECTOR2& pos, double size,float degree = 180);
	virtual ~cBullet();

	virtual void Update() PURE;
	void Render();

	bool IsOutMap();
	void SetColMouse(bool coll) { bCollMouse = coll; }
	bool GetColMouse() { return bCollMouse; } 
	void SetDegree(float degree) { m_degree = degree; } 
	bool& isDead() { return m_dead; } 
}; 