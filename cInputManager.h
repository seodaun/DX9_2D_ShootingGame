#pragma once

#ifndef _CINPUTMANAGER_H_
#define _CINPUTMANAGER_H_
#include"singleton.h"

enum class BGM_STATE{LOBBY, INGAME};

class CFMODSound;
class cInputManager :public singleton<cInputManager>
{
private:
	bool m_NowKeys[256] = { false, };
	bool m_OldKeys[256] = { false, };

	bool NowMouse[2] = { false, };
	bool OldMouse[2] = { false, };
public:
	cInputManager();
	virtual ~cInputManager();

	void Init();
	void Update();

	POINT GetScrollPos();
	POINT GetMousePos();
public:
	bool KeyDown(int i) { return !m_OldKeys[i] && m_NowKeys[i]; }
	bool KeyUp(int i) { return m_OldKeys[i] && !m_NowKeys[i]; }
	bool KeyPress(int i) { return m_OldKeys[i] && m_NowKeys[i]; }

	bool MouseLPress() { return (NowMouse[0] == true && OldMouse[0] == true); };
	bool MouseLUp() { return (NowMouse[0] == false && OldMouse[0] == true); };
	bool MouseLDown() { return (NowMouse[0] == true && OldMouse[0] == false); };

	bool MouseRPress() { return (NowMouse[1] == true && OldMouse[1] == true); };
	bool MouseRUp() { return (NowMouse[1] == false && OldMouse[1] == true); };
	bool MouseRDown() { return (NowMouse[1] == true && OldMouse[1] == false); };

public:
	CFMODSound fmod;
	BGM_STATE m_nCurrentBGM;
	bool BGM_on;
	bool isBGM_On() { return BGM_on; }
	
};


#define BGM_OFF			cInputManager::GetInstance()->BGM_on = false
#define BGM_ON			cInputManager::GetInstance()->BGM_on = true
#define CurBGM			cInputManager::GetInstance()->m_nCurrentBGM
#define FMOD			cInputManager::GetInstance()->fmod
#define SOUNDMANAGER	cInputManager::GetInstance()
#define INPUTMANAGER	cInputManager::GetInstance()
#define KEY_DOWN(vk)	INPUTMANAGER->KeyDown(vk)
#define KEY_UP(vk)		INPUTMANAGER->KeyUp(vk)
#define KEY_PRESS(vk)	INPUTMANAGER->KeyPress(vk)

#endif 