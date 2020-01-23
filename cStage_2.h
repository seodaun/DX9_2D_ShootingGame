#pragma once
class cFps;
class cScroolMap;
class cPlayer;
class cBulletAdmin;
class cEnemy_1;
class cEnemyAdmin;
class cBullet;
class cStage_2
{
private:
	cScroolMap* m_map;
	cPlayer* m_player;
	cBulletAdmin* m_PBulletAd;
	cBulletAdmin* m_EBulletAd;
	cEnemyAdmin* m_EnemyAd;
	cFps* m_EnemySpawnTime;
	cFps* m_startSpawn;
	cFps* m_bulletSpawnTime; 
	vector<cBullet*> m_fireBullet;
	bool bSpawn;
	int m_hp;
	float m_pctAnglerSpawn = 0.8f;
	float m_pctFishSpawn = 0.5f;
	float m_pctSquidSpawn = 0.3f;
private:
	bool m_clear;
	bool binit = false;
public:
	cStage_2();
	~cStage_2();

	void Init();
	void Update();
	void Render();
	void Release();

	bool isClear() { return m_clear; }
};

