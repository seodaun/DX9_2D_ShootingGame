#include "DXUT.h"
#include "cTitleScene.h" 
#include "cInputManager.h"
#include "cButton.h"
#include "cFps.h"
cTitleScene::cTitleScene()
{
}

cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{  
	m_StartBtn = new cButton(960, 540, "TitleBg");
	m_StartBtn->Init();
}

void cTitleScene::Update()
{   
	if (m_StartBtn->Update()) {
		SCENEMANAGER->ChangeScene("Lobby");
	}
}

void cTitleScene::Render()
{
	m_StartBtn->Render();
}

void cTitleScene::Release()
{ 
	SAFE_DELETE(m_StartBtn);
}
