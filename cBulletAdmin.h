#pragma once

class cBullet;
class cEnemy;
class cBulletAdmin
{
private:
	vector<cBullet*> m_PBullet;
	vector<cBullet*> m_EBullet; 
	int m_bulletspeed; 
public:
	cBulletAdmin();
	~cBulletAdmin();

	void Reset();

	void Update();
	void Render(); 
	void FirePBullet(cBullet* bullet) { m_PBullet.push_back(bullet); }
	void FireEBullet(cBullet* bullet) { m_EBullet.push_back(bullet); }
	vector<cBullet*>& GetPBullet() { return m_PBullet; }
	vector<cBullet*>& GetEBullet() { return m_EBullet; }

};

