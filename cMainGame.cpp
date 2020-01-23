#include "DXUT.h"
#include "cMainGame.h"

// 씬 include 
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
	// 여기서 각 씬들을 모두 추가
	SCENEMANAGER->AddScene("Load", new cLoadScene);
	SCENEMANAGER->AddScene("Title", new cTitleScene);
	SCENEMANAGER->AddScene("Ingame", new cInGameScene);   
	SCENEMANAGER->AddScene("Lobby", new cLobbyScene);  
	 
	// 첫번째 씬 배정
	SCENEMANAGER->ChangeScene("Load");
}

void cMainGame::Update()
{
	SCENEMANAGER->Update();
	INPUTMANAGER->Update();
}

void cMainGame::Render()
{
	// 다이렉트 X 의 그래픽 처리는 sprite객체로 처리되기 때문에
	// 렌더 작업 전 Begin() 작업 후에 End() 함수를 호출함

	IMAGEMANAGER->Begin();

	SCENEMANAGER->Render();

	IMAGEMANAGER->End();

}

void cMainGame::Release()
{  
	// maingame 클래스의 해제 코드 추가 : 
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
