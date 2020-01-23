#pragma once
using namespace std;
class cBullet; 
class cEnemy;
class cEnemyAdmin
{
public:
	cEnemyAdmin();
	~cEnemyAdmin();

private: 
	vector<cEnemy*> m_Enemy; 
	int eraseBullet;
	int cntDeadEnemy;

public:
	void Update();
	void Render();    
	int getDeadEnemy() { return cntDeadEnemy; }
	vector<cEnemy*>& GetEnemy() { return m_Enemy; }
};

