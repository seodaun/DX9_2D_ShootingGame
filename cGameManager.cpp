#include "DXUT.h"
#include "cGameManager.h"
#include <string>

cGameManager::cGameManager()
{
}

cGameManager::~cGameManager()
{
	Release();
}

void cGameManager::Init()
{
	m_Money = 100;
	m_Stage = 1;	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			SkillGauge[i][j] = IMAGEMANAGER->FindImage("P"+to_string(i+1)+"_Skill_" + to_string(j));
		}
	}
	m_Character = CHARACTER::eJELLYFISH;
	for (int c = 0; c < CHARACTER_KIND; c++)
		for (int s = 0; s < SKILL_KIND; s++)
			m_SkillStat[c][s] = 1;
	m_Player = new cPlayer();
	m_Player->Init();
	m_EBulletAd = new cBulletAdmin();
	m_PBulletAd = new cBulletAdmin();
	m_EnemyAd = new cEnemyAdmin();
	m_MaxStat[eJELLYFISH][HP] = 6;
	m_MaxStat[eJELLYFISH][BULLET] = 2;
	m_MaxStat[eJELLYFISH][SKILL] = 3;
	m_MaxStat[eLOBSTER][HP] = 2;
	m_MaxStat[eLOBSTER][BULLET] = 1;
	m_MaxStat[eLOBSTER][SKILL] = 3;
	m_MaxStat[eSTINGRAY][HP] = 3;
	m_MaxStat[eSTINGRAY][BULLET] = 3;
	m_MaxStat[eSTINGRAY][SKILL] = 3; 

}

void cGameManager::Release()
{ 
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_EBulletAd);
	SAFE_DELETE(m_PBulletAd);
	SAFE_DELETE(m_EnemyAd);
}

void cGameManager::ResetAdmin()
{
	SAFE_DELETE(m_EBulletAd);
	SAFE_DELETE(m_PBulletAd);
	SAFE_DELETE(m_EnemyAd);
	m_EBulletAd = new cBulletAdmin();
	m_PBulletAd = new cBulletAdmin();
	m_EnemyAd = new cEnemyAdmin();
}

void cGameManager::UpgradeStat(CHARACTER c, SKILL_STAT s)
{
	if (m_Money >= m_SkillStat[c][s] * 10) {
		if (chkSkillStat(c, s)) {
			m_Money -= m_SkillStat[c][s] * 10;
			m_SkillStat[c][s] += 1;
		}
	}
}
