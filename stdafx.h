#pragma once

#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <list>
#include <map>
#include "cSoundManager.h"

using namespace std;

// 화면의 크기

#define WINSIZEX 1920
#define WINSIZEY 1080

#define g_device	DXUTGetD3D9Device()		// 디바이스
#define deltaTime	DXUTGetElapsedTime()	// 프레임 지연 시간
#define g_nowTime	timeGetTime()			// 현재 시간
#define g_hWnd		DXUTGetHWND()			// 화면 핸들

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
// DEBUG_LOG : 콘솔 창에 로그를 표시합니다.

#if _DEBUG
#define DEBUG_LOG(log) cout << log << endl
#else
#define DEBUG_LOG(lob)  
#endif 
// 매니저 추가
#include "cSceneManager.h"
#include "cImgManager.h"
#include "cInputManager.h" 
#include "cGameManager.h"