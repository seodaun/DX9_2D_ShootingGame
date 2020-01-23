
#include "DXUT.h"  
#include <iostream> 
#include "cInGameScene.h" 
#include "cStage_1.h"
#include "cStage_2.h"
#include "cStage_3.h"  
#include "cButton.h"
#include <string>
#define MAX_STAGE 3
using namespace std;
cInGameScene::cInGameScene()
{

}

cInGameScene::~cInGameScene()
{
}


void cInGameScene::Init()
{
	m_stage = GAMEMANAGER->getStage();
	m_stage_1 = new cStage_1; 
	m_stage_2 = new cStage_2; 
	m_stage_3 = new cStage_3; 
	m_stage_1->Init();
	m_stage_2->Init();
	m_stage_3->Init();
	m_back = new cButton(989,599,"BackBtn");
	m_back->Init();
	m_restart = new cButton(989, 699, "RestartBtn");
	m_restart->Init();
	m_continue = new cButton(989, 499, "ContinueBtn");
	m_continue->Init();
}

void cInGameScene::Update()
{
	if (!bPause) {
		switch (m_stage) {
		case 1: { 
			m_stage_1->Update();
			if (m_stage_1->isClear()) {  
				GAMEMANAGER->setStage(2);
				GAMEMANAGER->resetKill();
				SCENEMANAGER->ChangeScene("Lobby");
			}
			break;
		}
		case 2: { 
			m_stage_2->Update();
			if (m_stage_2->isClear()) { 
				GAMEMANAGER->setStage(3);
				GAMEMANAGER->resetKill();
				SCENEMANAGER->ChangeScene("Lobby");
			}
			break;
		}
		case 3: { 
			m_stage_3->Update();
			if (m_stage_3->isClear()) {  
				m_stage_3->setClear(false);
				GAMEMANAGER->setStage(3);
				GAMEMANAGER->resetKill();
				SCENEMANAGER->ChangeScene("Lobby");
			}
			break;
		}
		}
	}
	else{
		if (m_back->Update()) {
			bPause = false;
			GAMEMANAGER->ResetAdmin();
			SCENEMANAGER->ChangeScene("Lobby");
		}
		if (m_restart->Update()) {
			GAMEMANAGER->ResetAdmin();
			Release();
			Init();
			bPause = false;
		}
		if (m_continue->Update()) { 
			bPause = false;
		}
	}
	if (INPUTMANAGER->KeyUp(9)) {
		bPause = bPause == true ? false : true;
	}
	
}

void cInGameScene::Render()
{
	switch (m_stage) {
	case 1: {
		m_stage_1->Render();
		break;
	}
	case 2: {
		m_stage_2->Render();
		break;
	}
	case 3: {
		m_stage_3->Render();
		break;
	}
	}
	string a = to_string(GAMEMANAGER->getCntKill());
	FONTMANAGER->sDrawText(1500, 100,a+"/20" , 100);

	 a = to_string(GAMEMANAGER->getStage());
	FONTMANAGER->sDrawText(1500, 200, "Stage: "+a, 100);
	if (bPause) {
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("PauseBg"), 0, 0, 1);
		m_back->Render();
		m_continue->Render();
		m_restart->Render();
	}
}

void cInGameScene::Release()
{
	SAFE_DELETE(m_stage_1);
	SAFE_DELETE(m_stage_2);
	SAFE_DELETE(m_stage_3);
	SAFE_DELETE(m_back);
	SAFE_DELETE(m_restart);
	SAFE_DELETE(m_continue);
}