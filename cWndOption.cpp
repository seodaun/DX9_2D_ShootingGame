#include "DXUT.h"
#include "cWndOption.h"
#include "cButton.h"
cWndOption::cWndOption()
{
}

cWndOption::~cWndOption()
{
	Release();
}

void cWndOption::Init()
{
	isClick_X = false;
	m_X = new cButton(1250, 80, "X");
	m_X->Init();
	m_Music = new cButton(900, 450, "Music");
	m_Music->Init();
	m_Credits = new cButton(900, 750, "Credits");
	m_Credits->Init();
}
void cWndOption::Update()
{
	if (m_X->Update()) isClick_X = true;  
	if (!isClick_X) {
		if(m_Music->Update()){
			if (SOUNDMANAGER->isBGM_On()) {
				BGM_OFF;
				if (CurBGM == BGM_STATE::LOBBY)
					FMOD.StopBG("Lobby");
				else
					FMOD.StopBG("IngameSound");
			}
			else {
				BGM_ON;
				if (CurBGM == BGM_STATE::LOBBY)
					FMOD.PlayBG("Lobby");
				else
					FMOD.PlayBG("IngameSound");
			}
		}
		if (m_Credits->Update()) {}
	}
}

void cWndOption::Render()
{
	if (!isClick_X) {
		IMAGEMANAGER->Render(IMAGEMANAGER->FindImage("OptionBg"), 500, 10, 1, 0);
		m_Music->Render();
		m_Credits->Render();
		m_X->Render();
	}
}


void cWndOption::Release()
{
	SAFE_DELETE(m_X);
	SAFE_DELETE(m_Music);
	SAFE_DELETE(m_Credits);
}
