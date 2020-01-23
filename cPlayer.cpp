#include "DXUT.h" 
#include "stdafx.h"
#include "cPlayer.h"
#include "cPlayerBullet.h"  
#include "cEnemy.h"
#include"cInputManager.h"  
#include <string>
#include <cmath>
#include "cFps.h"
#define PLAYERSPEED 300	 
#define PLAYERSIZE 110

#define COLLRANGE_X 300
#define COLLRANGE_Y WINSIZEY
#define RADIUS 250 

cPlayer::cPlayer()
{
}

cPlayer::~cPlayer()
{
	Release();
}
void cPlayer::StatInit()
{
	m_pState = eIDLE; 
	m_Gauge = 0;
	m_character = GAMEMANAGER->getCharacter();
	m_hp = GAMEMANAGER->getStat(GAMEMANAGER->getCharacter(), SKILL_STAT::HP);
	m_bulletSpeed = GAMEMANAGER->getStat(GAMEMANAGER->getCharacter(), SKILL_STAT::BULLET);
	m_skill = GAMEMANAGER->getStat(GAMEMANAGER->getCharacter(), SKILL_STAT::SKILL);
	GAMEMANAGER->resetKill();
	for (int i = 0; i < 6; i++) m_SkillGauge[i] = GAMEMANAGER->getSkillGauge(m_character, i);
}

void cPlayer::Init()
{
	m_playerPos.x = 200;
	m_playerPos.y = 500;
	StatInit(); 
	m_InvincibleFps = new cFps();
	m_playerImage[eJELLYFISH] = IMAGEMANAGER->FindImage("Player_" + to_string(eJELLYFISH + 1));
	m_playerImage[eLOBSTER] = IMAGEMANAGER->FindImage("Player_" + to_string(eLOBSTER + 1));
	m_playerImage[eSTINGRAY] = IMAGEMANAGER->FindImage("Player_" + to_string(eSTINGRAY + 1));
	for (int i = 0; i < CHARACTER_KIND; i++) {
		m_PlayerAni[i][eIDLE] = new cAnimation("IdlePlayer_" + to_string(i + 1), 0.08f, true);
		m_PlayerAni[i][eDAMAGE] = new cAnimation("DamagePlayer_" + to_string(i + 1), 0.08f, false);
		m_PlayerAni[i][eDIE] = new cAnimation("DiePlayer_" + to_string(i + 1), 0.08f, false);
	}  m_cntKillEnemy = 0;
	m_skillFullAni = new cAnimation("SkillFull", 0.08f, false);
	m_DamageBgAni = new cAnimation("DamageBg", 0.08f, false);
	bDamage = false;
}

void cPlayer::Release()
{
	for (int i = 0; i < CHARACTER_KIND; i++)
		for (int j = 0; j < STATE_KIND; j++)
			SAFE_DELETE(m_PlayerAni[i][j]);
	SAFE_DELETE(m_InvincibleFps);
	SAFE_DELETE(m_skillFullAni); 
	SAFE_DELETE(m_DamageBgAni);
}
void cPlayer::Update()
{   
	m_cntKillEnemy = GAMEMANAGER->getCntKill();
	m_Gauge = m_cntKillEnemy / 2;
	if (m_Gauge == 5) {
		bskillfull = true;
	}
	if (bskillfull)
		m_skillFullAni->Update();
	POINT mousePos = INPUTMANAGER->GetMousePos();
	cBullet* iter = bMouseColl(mousePos);
	Fire(iter, mousePos);
	if (INPUTMANAGER->KeyPress(32) && m_Gauge == 5) { //스킬 사용
		m_bSkill = true;
	}
	if (m_bInvincible && m_InvincibleFps->Timer(m_InvincibleTime))//무적해제 
		m_bInvincible = false;
	if (m_bSkill) {
		switch (m_character) {
		case CHARACTER::eJELLYFISH:	JellyfishSkill();break;
		case CHARACTER::eLOBSTER:	LobsterSkill();	 break;
		case CHARACTER::eSTINGRAY:	StingraySkill(); break;
		} 
	}
	switch (m_pState) {//애니메이션
	case CHARACTER_STATE::eIDLE:	if (m_PlayerAni[m_character][eIDLE]->Update())					 break;
	case CHARACTER_STATE::eDAMAGE:	if (m_PlayerAni[m_character][eDAMAGE]->Update())m_pState = eIDLE;break;
	case CHARACTER_STATE::eDIE:		if (m_PlayerAni[m_character][eDIE]->Update())	bDead = true;	 break;
	}  
	if (bDamage) {
		m_DamageBgAni->Update();
		if (!m_DamageBgAni->IsActive()) {
			bDamage = false;
			m_DamageBgAni->SetActive(true);
		}
	}
}
void cPlayer::Fire(cBullet* bullet,POINT mousepos)
{
	if (INPUTMANAGER->MouseLDown() && bullet != false) {//총알을 잡은 상태
		bullet->SetColMouse(true);
		m_beforePos = INPUTMANAGER->GetMousePos();
	}
	if (bCatchBullet() != false) {//총알을 잡고 있는 경우
		bullet = bCatchBullet();
		bullet->SetDegree(atan2f((bullet->m_pos.y - mousepos.y), (bullet->m_pos.x - mousepos.x)) * 180 / 3.1415f-180);
	}
	if (INPUTMANAGER->MouseLUp() && bCatchBullet() != false) {//총알을 잡았다 뗀 경우 
		bullet = bCatchBullet();
		(*bullet).isDead() = true;
		m_afterPos = INPUTMANAGER->GetMousePos();
		if (!m_succession) {
			if(m_afterPos.x != m_beforePos.x&& m_afterPos.y != m_beforePos.y)
				GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
					D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed));
			else
				GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
					D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x+1, m_afterPos.y), m_bulletSpeed));
		}
		else {
			Succession(bullet);
		}
	}
}
void cPlayer::Succession(cBullet* bullet)
{   
	m_cntBullet++;
	float asdf = atan2f((m_beforePos.y - m_afterPos.y), (m_beforePos.x - m_afterPos.x)) * 180 / 3.1415f - 90;
	switch (m_skill) {
	case 1: {
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf - 45));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf + 45)); break;
	}
	case 2: {
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf - 45));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf - 15));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf + 15));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf + 45)); break;
	}
	case 3: {
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf - 45));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf - 15));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf + 15));
		GAMEMANAGER->getPBulletAd()->FirePBullet(new cPlayerBullet(
			D3DXVECTOR2(m_beforePos.x, m_beforePos.y), D3DXVECTOR2(m_afterPos.x, m_afterPos.y), m_bulletSpeed, asdf + 45)); break;
	}
	}
	if (m_cntBullet == m_MaxBullet) { 
		m_cntBullet = 0;
		m_succession = false;
	}
} 
void cPlayer::Render()
{  
	switch (m_pState) {
	case CHARACTER_STATE::eIDLE:	m_PlayerAni[m_character][eIDLE]->CenterRender(m_playerPos.x, m_playerPos.y, 1, 0);	break;
	case CHARACTER_STATE::eDAMAGE:	m_PlayerAni[m_character][eDAMAGE]->CenterRender(m_playerPos.x, m_playerPos.y, 1, 0);	break;
	case CHARACTER_STATE::eDIE:		m_PlayerAni[m_character][eDIE]->CenterRender(m_playerPos.x, m_playerPos.y, 1, 0);	break;
	} 
	IMAGEMANAGER->Render(m_SkillGauge[m_Gauge], 1700, 720, 1); 
	if (bskillfull&& m_Gauge==5) {
		m_skillFullAni->CenterRender(1769, 808, 1,0);
		if (m_skillFullAni->IsActive()) {  
			m_skillFullAni->SetActive(false);
		}
	}

	if (bDamage) {
		m_DamageBgAni->Render(0,0,1,0);
	}
}

void cPlayer::PlayerColl() //적의 총알과 충돌
{
	RECT col = { 0,0,m_playerImage[m_character]->info.Width,m_playerImage[m_character]->info.Height };
	RECT playerRect = {
			(LONG)m_playerPos.x - PLAYERSIZE / 2,(LONG)m_playerPos.y - PLAYERSIZE / 2,
			(LONG)m_playerPos.x + PLAYERSIZE / 2, (LONG)m_playerPos.y + PLAYERSIZE / 2 };
	for (auto iter = GAMEMANAGER->getEBulletAd()->GetEBullet().begin(); iter != GAMEMANAGER->getEBulletAd()->GetEBullet().end();) {
		RECT enemyBulletRe = {
			(LONG)((*iter)->m_pos.x - (*iter)->m_image->info.Width / 2),
			(LONG)((*iter)->m_pos.y - (*iter)->m_image->info.Height / 2),
			(LONG)((*iter)->m_pos.x + (*iter)->m_image->info.Width / 2),
			(LONG)((*iter)->m_pos.y + (*iter)->m_image->info.Height / 2) };
		if (IntersectRect(&col, &enemyBulletRe, &playerRect)) {
			Damage(1);
			(*iter)->isDead() = true; 
		}
		iter++;
	} 
}
void cPlayer::JellyfishSkill()
{
	if (m_skill == 1)maxHp=1;
	if (m_skill == 2)maxHp=2;
	if (m_skill == 3)maxHp=3;
	if (m_skill == 1)Heal(1);
	if (m_skill == 2)Heal(2);
	if (m_skill == 3)Heal(3);
	m_bSkill = false;
}
void cPlayer::LobsterSkill()
{
	m_succession = true;
	m_bSkill = false;
	if (m_skill == 1)m_MaxBullet = 5;
	if (m_skill == 2)m_MaxBullet = 5;
	if (m_skill == 3)m_MaxBullet = 6;
}

void cPlayer::StingraySkill()
{ 
	m_bInvincible = true;
	m_bSkill = false;
	m_InvincibleFps->SetStartTime();
	if (m_skill == 1)m_InvincibleTime = 5;
	if (m_skill == 2)m_InvincibleTime = 6.5;
	if (m_skill == 3)m_InvincibleTime = 8;
}

bool cPlayer::bMouseColl(D3DXVECTOR2 bulletpos, POINT mousepos, int w, int h)//마우스와 총알 충돌체크
{
	RECT col = { 0,0,w,h };
	RECT MouseRe = { (LONG)mousepos.x - 15,(LONG)mousepos.y - 15,(LONG)mousepos.x + 15,(LONG)mousepos.y + 15 };
	RECT bulletRe = { (LONG)(bulletpos.x - w / 2), (LONG)(bulletpos.y - h / 2),(LONG)(bulletpos.x + w / 2), (LONG)(bulletpos.y + h / 2) };
	return IntersectRect(&col, &MouseRe, &bulletRe);//충돌했는지 체크하는 함수 
}

cBullet* cPlayer::bMouseColl(POINT mousePos)//마우스와 총돌한 총알 반환
{
	float length;
	for (auto iter = GAMEMANAGER->getEBulletAd()->GetEBullet().begin(); iter != GAMEMANAGER->getEBulletAd()->GetEBullet().end();) {
		length = sqrt(pow((*iter)->m_pos.x - m_playerPos.x, 2) + pow((*iter)->m_pos.y - m_playerPos.y, 2));
		if (bMouseColl((*iter)->m_pos, mousePos, (*iter)->m_image->info.Width, (*iter)->m_image->info.Height) && length <= RADIUS)
			return (*iter);
		iter++;
	}return false;
}

cBullet* cPlayer::bCatchBullet()
{ 
	for (auto iter = GAMEMANAGER->getEBulletAd()->GetEBullet().begin(); iter != GAMEMANAGER->getEBulletAd()->GetEBullet().end();) {
		if ((*iter)->GetColMouse()) { 
			return (*iter);
		}
		iter++; 
	}return false;
} 

 