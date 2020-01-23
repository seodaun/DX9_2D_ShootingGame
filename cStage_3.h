#pragma once
class cFps;
class cScroolMap;
class cPlayer;
class cBulletAdmin;
class cEnemy_1;
class cEnemyAdmin;
class cBullet;
class cStage_3
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
	vector<cBullet*> m_fireBullet;
	bool bSpawn;
	int m_hp;
	float m_pctAnglerSpawn = 1.f;
	float m_pctFishSpawn = 0.8f;
	float m_pctSquidSpawn = 0.4f;
private:
	bool m_clear;
	bool binit = false;
public:
	cStage_3();
	~cStage_3();

	void Init();
	void Update();
	void Render();
	void Release();

	bool isClear() { return m_clear; }
	void setClear(bool b) { m_clear = b; }
};

