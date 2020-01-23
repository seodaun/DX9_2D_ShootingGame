#include "DXUT.h"
#include "cStage_3.h"
#include "cFps.h"
#include "cScroolMap.h" 
#include "cBulletAdmin.h" 
#include "cPlayer.h"
#include "cEnemyAdmin.h"
#include "cAnglerfish.h"
#include "cFish.h"
#include "cSquid.h"
#include "cEnemyBullet.h"
#include "cBullet.h"
#include "cGameManager.h"
#include <time.h>  


cStage_3::cStage_3()
{
}

cStage_3::~cStage_3()
{
	Release();
}

void cStage_3::Init()
{
	m_EnemySpawnTime = new cFps;
	m_bulletSpawnTime = new cFps;
	m_startSpawn = new cFps;
	m_map = new cScroolMap("SeaBg");
	m_PBulletAd = GAMEMANAGER->getPBulletAd();
	m_EBulletAd = GAMEMANAGER->getEBulletAd();
	m_EnemyAd = GAMEMANAGER->getEnemyAd();
	m_player = GAMEMANAGER->getPlayer();
	m_player->StatInit(); 
	m_clear = false;
	bSpawn = false;
	m_hp = 0;
}
void cStage_3::Release()
{
	SAFE_DELETE(m_map);
	SAFE_DELETE(m_bulletSpawnTime);
	SAFE_DELETE(m_EnemySpawnTime);
	SAFE_DELETE(m_startSpawn);
}

void cStage_3::Update()
{
	if (!binit) {
		m_EnemySpawnTime->SetStartTime();
		m_bulletSpawnTime->SetStartTime();
		m_startSpawn->SetStartTime();
		binit = true;
	}
	m_hp = m_player->getHp();
	srand(time(NULL));
	if (m_startSpawn->Timer(3500)) bSpawn = true;
	if (m_EnemySpawnTime->Timer(2 * 1000) && GAMEMANAGER->getSpawnEnemy() != 20&& bSpawn)
	{
		int nRandom = (rand() % 100 + 1) / 100;
		if (nRandom / 100 <= m_pctSquidSpawn)
			m_EnemyAd->GetEnemy().push_back(new cSquid({ WINSIZEX, (float)((rand() % 5 + 1) * 180) }, m_player->GetPos(), 3));
		else if (nRandom / 100 <= m_pctFishSpawn)
			m_EnemyAd->GetEnemy().push_back(new cFish({ WINSIZEX, (float)((rand() % 5 + 1) * 180) }, m_player->GetPos(), 2));
		else
			m_EnemyAd->GetEnemy().push_back(new cAnglerfish({ WINSIZEX, (float)((rand() % 5 + 1) * 180) }, m_player->GetPos(), 1));
		GAMEMANAGER->setSpawnEnemy(GAMEMANAGER->getSpawnEnemy() + 1);
		m_EnemySpawnTime->SetStartTime();
	}
	if (m_bulletSpawnTime->Timer(1 * 1000)) {
		m_EBulletAd->GetEBullet().push_back(new cEnemyBullet(D3DXVECTOR2(WINSIZEX - 100, WINSIZEY / 2), m_player->GetPos()));
		m_bulletSpawnTime->SetStartTime();
	}
	m_map->Update(100);
	m_player->Update();
	m_PBulletAd->Update();
	m_EnemyAd->Update();
	m_EBulletAd->Update();

	if (m_player->chkDead()) {
		m_player->StatInit();
		GAMEMANAGER->ResetAdmin();
		SCENEMANAGER->ChangeScene("Lobby");
	}
	if (GAMEMANAGER->getCntKill() == 20) {
		m_clear = true;
	}
}

void cStage_3::Render()
{
	m_map->Render();
	m_player->Render();
	m_PBulletAd->Render();
	m_EBulletAd->Render();
	m_EnemyAd->Render();
	for (int i = 0; i < m_hp; i++)
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("Hp_icon"), 200 + 100 * (i + 1), 50, 1, 0);
}

