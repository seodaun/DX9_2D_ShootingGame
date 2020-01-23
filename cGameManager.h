#pragma once
#include "singleton.h"
#include "stdafx.h"
#include "cPlayer.h"
#include "cBulletAdmin.h"
#include "cEnemyAdmin.h" 
class cGameManager :
	public singleton<cGameManager>
{
private:
	cPlayer* m_Player = nullptr;
	cEnemyAdmin* m_EnemyAd = nullptr;
	cBulletAdmin* m_EBulletAd = nullptr; 
	cBulletAdmin* m_PBulletAd = nullptr; 
	texture* SkillGauge[CHARACTER_KIND][6] = { nullptr, };
	int m_Stage=1;
	int m_Money;
	CHARACTER m_Character;
	int m_SkillStat[CHARACTER_KIND][SKILL_KIND];
	int m_MaxStat[CHARACTER_KIND][SKILL_KIND]; 
	int cntDieEnemy=0; //죽은 적 카운트
	int GcntDieEnemy=0; //죽은 적 카운트
	int cntSpawnEnemy = 0; 
private:
	bool chkSkillStat(CHARACTER c, SKILL_STAT s) {
		if (m_SkillStat[c][s] == m_MaxStat[c][s])
			return false;
		else 
			return true;
	}
public:
	cGameManager();
	~cGameManager();
	void Init(); 
	void Release();
	void ResetAdmin();
public:
	cPlayer* getPlayer() { return m_Player; }
	cEnemyAdmin* getEnemyAd() { return m_EnemyAd; }
	cBulletAdmin* getPBulletAd() { return m_PBulletAd; }
	cBulletAdmin* getEBulletAd() { return m_EBulletAd; } 
	texture* getSkillGauge(CHARACTER c, int i) { 
		return SkillGauge[c][i];
	}
	int getStage() { return m_Stage; }
	int getMoney() { return m_Money; }
	void earnMoney(int m) { m_Money += m; }
	CHARACTER getCharacter() { return m_Character; }
	int getStat(CHARACTER p, SKILL_STAT s) { return m_SkillStat[p][s]; } 
public:
	void setStage(int s) { m_Stage = s; }
	void setCharacter(CHARACTER c) { m_Character = c; }
	void UpgradeStat(CHARACTER c, SKILL_STAT s);
	void cntKill() { cntDieEnemy += 1; };
	int getKillE() { return cntDieEnemy; };
	int getCntKill() { return cntDieEnemy >= 10 ? 10 : cntDieEnemy; };
	void resetKill() { cntDieEnemy = 0; };
	int getSpawnEnemy() { return cntSpawnEnemy; }
	void setSpawnEnemy(int cnt) { cntSpawnEnemy += cnt; } 
};

#define GAMEMANAGER cGameManager::GetInstance()