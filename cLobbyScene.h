#pragma once
#include "cScene.h"
#include "stdafx.h" 
class cFileIO;
class cButton;
class cWndOption;
//class CFMODSound;
class cLobbyScene : public cScene
{
public:
	cLobbyScene();
	virtual ~cLobbyScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	void StatUpgrade(CHARACTER character, SKILL_STAT s);
	void ChangeCharacter() { GAMEMANAGER->setCharacter(m_character); } 
private:
	cButton* m_Jellyfish;
	cButton* m_Stingray; 
	cButton* m_Lobster;
	cButton* m_Back;
	cButton* m_Start;
	cButton* m_Qu;
	cButton* m_Help;
	cButton* m_X;
	cButton* m_LvUp1;
	cButton* m_LvUp2;
	cButton* m_LvUp3;
	cButton* m_Music;
	cButton* m_Credits;

	//CFMODSound* fmod;
	cWndOption* m_WndOption;
private:
	cFileIO* m_file;  
	int m_pSkillStat[3][3];
	CHARACTER m_character;

	bool bOption;
	bool isClick_Help; 
	bool isClick_Qu;
	int m_money;
};
