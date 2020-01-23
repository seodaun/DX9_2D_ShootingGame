#include "DXUT.h"
#include "cMainGame.h"

// �� include 
#include "cLoadScene.h"
#include "cTitleScene.h"
#include "cInGameScene.h" 
#include "cStage_1.h" 
#include "cLobbyScene.h" 
#include "cInputManager.h"
#include "cGameManager.h"
#include <fstream>
void cMainGame::Init()
{   
	// ���⼭ �� ������ ��� �߰�
	SCENEMANAGER->AddScene("Load", new cLoadScene);
	SCENEMANAGER->AddScene("Title", new cTitleScene);
	SCENEMANAGER->AddScene("Ingame", new cInGameScene);   
	SCENEMANAGER->AddScene("Lobby", new cLobbyScene);  
	 
	// ù��° �� ����
	SCENEMANAGER->ChangeScene("Load");
}

void cMainGame::Update()
{
	SCENEMANAGER->Update();
	INPUTMANAGER->Update();
}

void cMainGame::Render()
{
	// ���̷�Ʈ X �� �׷��� ó���� sprite��ü�� ó���Ǳ� ������
	// ���� �۾� �� Begin() �۾� �Ŀ� End() �Լ��� ȣ����

	IMAGEMANAGER->Begin();

	SCENEMANAGER->Render();

	IMAGEMANAGER->End();

}

void cMainGame::Release()
{  
	// maingame Ŭ������ ���� �ڵ� �߰� : 
	cImageManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cInputManager::ReleaseInstance(); 
	cGameManager::ReleaseInstance();
}


void cMainGame::OnLostDevice()
{
	IMAGEMANAGER->OnLostDevice();
}

void cMainGame::OnResetDevice()
{
	IMAGEMANAGER->OnLostDevice();
}
