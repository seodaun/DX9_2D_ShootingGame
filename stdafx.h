#pragma once

#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <list>
#include <map>
#include "cSoundManager.h"

using namespace std;

// ȭ���� ũ��

#define WINSIZEX 1920
#define WINSIZEY 1080

#define g_device	DXUTGetD3D9Device()		// ����̽�
#define deltaTime	DXUTGetElapsedTime()	// ������ ���� �ð�
#define g_nowTime	timeGetTime()			// ���� �ð�
#define g_hWnd		DXUTGetHWND()			// ȭ�� �ڵ�

enum CHARACTER {
	eJELLYFISH=0,
	eLOBSTER,
	eSTINGRAY
};
enum ENEMYS {
	eANGLERFISH,
	eFISH,
	eSQUID
};
enum SKILL_STAT {
	HP,
	BULLET,
	SKILL
}; 
enum CHARACTER_STATE {
	eIDLE,
	eDAMAGE,
	eDIE
};
enum BULLET_STATE {
	IDLE,
	DIE
};
#define CHARACTER_KIND 3
#define SKILL_KIND 3 
#define STATE_KIND 3  
// 
// DEBUG_LOG : �ܼ� â�� �α׸� ǥ���մϴ�.

#if _DEBUG
#define DEBUG_LOG(log) cout << log << endl
#else
#define DEBUG_LOG(lob)  
#endif 
// �Ŵ��� �߰�
#include "cSceneManager.h"
#include "cImgManager.h"
#include "cInputManager.h" 
#include "cGameManager.h"