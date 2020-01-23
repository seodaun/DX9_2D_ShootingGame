#include "DXUT.h"
#include "cInputManager.h"

cInputManager::cInputManager()
{
	Init();
}
cInputManager::~cInputManager()
{
	fmod.Release();
}

void cInputManager::Init()
{
	BGM_on = true;
	m_nCurrentBGM = BGM_STATE::LOBBY;
	fmod.AddBGSound("Lobby", "BGM/Lobby.mp3");
	fmod.AddBGSound("IngameSound", "BGM/IngameSound.mp3");

	fmod.AddEFSound("Button", "SOUNDEFFECT/water_Button.mp3");
	fmod.AddEFSound("Death", "SOUNDEFFECT/Monster_Death_1.mp3");
}

void cInputManager::Update()
{
	for (int i = 0; i < 2; i++) OldMouse[i] = NowMouse[i];
	memcpy(&m_OldKeys, m_NowKeys, sizeof(bool) * 256);
	memset(&m_NowKeys, false, sizeof(bool) * 256);

	for (int i = 0; i < 256; i++) {
		m_NowKeys[i] = GetAsyncKeyState(i);
	}
	if (GetAsyncKeyState(VK_LBUTTON)) NowMouse[0] = true;
	else NowMouse[0] = false;

	if (GetAsyncKeyState(VK_RBUTTON)) NowMouse[1] = true;
	else NowMouse[1] = false;
}

POINT cInputManager::GetMousePos()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(DXUTGetHWND(), &point);
	//Vector2 v_mousepos(point.x, point.y);
	return point;
}

