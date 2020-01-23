
#pragma once 
class cFps;
class cScroolMap;
class cPlayer;
class cBulletAdmin;
class cEnemy_1;
class cEnemyAdmin;
class cBullet; 
class CFMODSound;
class cStage_1  
{
private:
	cScroolMap* m_map;
	cPlayer* m_player;
	cBulletAdmin* m_PBulletAd;
	cBulletAdmin* m_EBulletAd;
	cEnemyAdmin* m_EnemyAd;
	cFps* m_EnemySpawnTime;
	cFps* m_bulletSpawnTime; 
	cFps* m_startSpawn; 
	CFMODSound* fmod;
	vector<cBullet*> m_fireBullet;
	bool bSpawn; 
	int m_hp;
	float m_pctAnglerSpawn = 0.02f;
	float m_pctFishSpawn = 0.4f;
	float m_pctSquidSpawn = 0.8f;
private:
	bool m_clear;
	bool binit = false;
public:
	cStage_1();
	~cStage_1();

	void Init()	;
	void Update();
	void Render();
	void Release();

	bool isClear() { return m_clear; }
};  