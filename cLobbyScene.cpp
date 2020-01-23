#include "DXUT.h" 
#include "cLobbyScene.h"
#include "cButton.h"  
#include "cWindow.h"
#include "cWndOption.h"
#include "cSoundManager.h"
#include <string>
#include <math.h>
#define FONT 70

cLobbyScene::cLobbyScene()
{ 
}

cLobbyScene::~cLobbyScene()
{  
}

void cLobbyScene::Init()
{ 
	bOption = false;

	//fmod = new CFMODSound;
	//fmod->AddBGSound("Lobby", "Lobby.mp3");
	//fmod->PlayBG("Lobby");
	if (SOUNDMANAGER->isBGM_On())
	FMOD.PlayBG("Lobby");
	//INPUTMANAGER->fmod->AddBGSound("Lobby", "Lobby.mp3");
	//INPUTMANAGER->fmod->PlayBG("Lobby");

	isClick_Help = false;
	isClick_Qu = false;
	m_Jellyfish = new cButton(1370, 224, "Jellyfish");
	m_Jellyfish->Init(0,0,44,0);
	m_Stingray = new cButton(1510, 224, "Stingray");
	m_Stingray->Init(0, 0, 30, 0);
	m_Lobster = new cButton(1680, 224, "Lobster");
	m_Lobster->Init(50, 0, 60, 0);
	m_Back = new cButton(65, 60, "Back");
	m_Back->Init();
	m_Start = new cButton(1500, 900, "start_btn");
	m_Start->Init();
	m_Help = new cButton(890, 60, "Help");
	m_Help->Init();
	m_Qu = new cButton(810, 60, "Q");
	m_Qu->Init();
	m_LvUp1 = new cButton(1525, 575, "Lvup");
	m_LvUp1->Init();
	m_LvUp2 = new cButton(1525, 655, "Lvup");
	m_LvUp2->Init();
	m_LvUp3 = new cButton(1525, 735, "Lvup");
	m_LvUp3->Init(); 
	m_WndOption = new cWndOption();
	m_WndOption->Init();  
	m_money = GAMEMANAGER->getMoney();
	switch (GAMEMANAGER->getCharacter()) {
	case CHARACTER::eJELLYFISH:	m_character = CHARACTER::eJELLYFISH;break;
	case CHARACTER::eLOBSTER:	m_character = CHARACTER::eLOBSTER;	break;
	case CHARACTER::eSTINGRAY:	m_character = CHARACTER::eSTINGRAY;	break;
	}   
	m_pSkillStat[CHARACTER::eJELLYFISH][HP] = GAMEMANAGER->getStat(eJELLYFISH, HP);
	m_pSkillStat[CHARACTER::eJELLYFISH][BULLET] = GAMEMANAGER->getStat(eJELLYFISH, BULLET);
	m_pSkillStat[CHARACTER::eJELLYFISH][SKILL] = GAMEMANAGER->getStat(eJELLYFISH, SKILL);
	m_pSkillStat[CHARACTER::eLOBSTER][HP] = GAMEMANAGER->getStat(eLOBSTER, HP);
	m_pSkillStat[CHARACTER::eLOBSTER][BULLET] = GAMEMANAGER->getStat(eLOBSTER, BULLET);
	m_pSkillStat[CHARACTER::eLOBSTER][SKILL] = GAMEMANAGER->getStat(eLOBSTER, SKILL);
	m_pSkillStat[CHARACTER::eSTINGRAY][HP] = GAMEMANAGER->getStat(eSTINGRAY, HP);
	m_pSkillStat[CHARACTER::eSTINGRAY][BULLET] = GAMEMANAGER->getStat(eSTINGRAY, BULLET);
	m_pSkillStat[CHARACTER::eSTINGRAY][SKILL] = GAMEMANAGER->getStat(eSTINGRAY, SKILL);
}


void cLobbyScene::StatUpgrade(CHARACTER character, SKILL_STAT stat)
{
	GAMEMANAGER->UpgradeStat(m_character, stat);
	m_pSkillStat[character][stat] = GAMEMANAGER->getStat(m_character, stat);
} 
void cLobbyScene::Update()
{
	FMOD.Update();
	if (!bOption) {
		if (!isClick_Help || !isClick_Qu) {
			if (m_Back->Update()) SCENEMANAGER->ChangeScene("Title");
			if (m_Start->Update()) SCENEMANAGER->ChangeScene("Ingame");
			if (m_Help->Update()) isClick_Help = true;
			if (m_Qu->Update())  isClick_Qu = true;
			if (m_LvUp1->Update()) StatUpgrade(m_character, HP);
			if (m_LvUp2->Update()) StatUpgrade(m_character, BULLET);
			if (m_LvUp3->Update()) StatUpgrade(m_character, SKILL);
			if (m_Jellyfish->Update()) { m_character = eJELLYFISH; ChangeCharacter(); }
			if (m_Stingray->Update()) { m_character = eSTINGRAY;   ChangeCharacter(); }
			if (m_Lobster->Update()) { m_character = eLOBSTER;	ChangeCharacter(); }
			if (isClick_Help) {
				bOption = true;

			}
		}
	}
	else {
		m_WndOption->Update();
		if (m_WndOption->getClickX()) {
			bOption = false;
			isClick_Help = false;
			m_WndOption->setClickX(false);
		}
	}
	m_money = GAMEMANAGER->getMoney();
}

void cLobbyScene::Render()
{
	IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("LobbyBg"), 0, 0, 1, 0);
	IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("GameMoney"), 935, 25, 1, 0);
	IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("Bullet_icon"), 1245, 600, 1, 0);
	IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("Hp_icon"), 1250, 530, 1, 0);
	IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("Skill_icon"), 1250, 690, 1, 0);
	IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("Coin_icon"), 940, 25, 1, 0);
	IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("CharSelect"), 1235, 140, 1, 0);
	m_Back->Render();
	m_Start->Render();
	m_Help->Render();
	m_Qu->Render();
	m_LvUp1->Render();
	m_LvUp2->Render();
	m_LvUp3->Render();
	m_Jellyfish->Render();
	m_Stingray->Render(); 
	m_Lobster->Render(); 
	int n;
	if (m_money == 0) { n = 0; }
	else n=log10(m_money);
	FONTMANAGER->sDrawText(1070-18*n, 30, to_string(m_money), 50);

	switch (m_character) {
	case CHARACTER::eJELLYFISH:
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("JellyfishChar"), 100, 5, 1, 0);
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("J_Skill"), 1620, 480, 1, 0);
		FONTMANAGER->sDrawText(1400, 540, to_string(m_pSkillStat[eJELLYFISH][HP]), FONT);
		FONTMANAGER->sDrawText(1400, 620, to_string(m_pSkillStat[eJELLYFISH][BULLET]), FONT);
		FONTMANAGER->sDrawText(1400, 700, to_string(m_pSkillStat[eJELLYFISH][SKILL]), FONT); break;
	case CHARACTER::eLOBSTER:
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("LobsterChar"), 100, 5, 1, 0);
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("L_Skill"), 1620, 480, 1, 0);
		FONTMANAGER->sDrawText(1400, 540, to_string(m_pSkillStat[eLOBSTER][HP]), FONT);
		FONTMANAGER->sDrawText(1400, 620, to_string(m_pSkillStat[eLOBSTER][BULLET]), FONT);
		FONTMANAGER->sDrawText(1400, 700, to_string(m_pSkillStat[eLOBSTER][SKILL]), FONT); break;
	case CHARACTER::eSTINGRAY:
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("StingrayChar"), 100, 5, 1, 0);
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("S_Skill"), 1620, 480, 1, 0);
		FONTMANAGER->sDrawText(1400, 540, to_string(m_pSkillStat[eSTINGRAY][HP]), FONT);
		FONTMANAGER->sDrawText(1400, 620, to_string(m_pSkillStat[eSTINGRAY][BULLET]), FONT);
		FONTMANAGER->sDrawText(1400, 700, to_string(m_pSkillStat[eSTINGRAY][SKILL]), FONT); break;
	}
	if (isClick_Help) { m_WndOption->Render(); }
}

void cLobbyScene::Release()
{
	SAFE_DELETE(m_Back);
	SAFE_DELETE(m_Start);
	SAFE_DELETE(m_Help);
	SAFE_DELETE(m_Qu);
	SAFE_DELETE(m_LvUp1);
	SAFE_DELETE(m_LvUp2);
	SAFE_DELETE(m_LvUp3);
	SAFE_DELETE(m_Stingray);
	SAFE_DELETE(m_Lobster);
	SAFE_DELETE(m_Jellyfish);
	SAFE_DELETE(m_WndOption); 
	//SAFE_DELETE(fmod);
	FMOD.StopBG("Lobby");
}