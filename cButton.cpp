#include "DXUT.h"
#include "cButton.h"
#include "cImgManager.h"
#include "cInputManager.h"

cButton::cButton(int x, int y, const string& key)
{
	m_Nomal = IMAGEMANAGER->FindImage(key + "_0");
	m_OnCursor = IMAGEMANAGER->FindImage(key + "_1");
	m_Click = IMAGEMANAGER->FindImage(key + "_2");

	m_Pos.x = x;
	m_Pos.y = y;
}
void cButton::Init()
{
	SetRect(&m_rt,
		m_Pos.x - m_Nomal->info.Width / 2,
		m_Pos.y - m_Nomal->info.Height / 2,
		m_Pos.x + m_Nomal->info.Width / 2,
		m_Pos.y + m_Nomal->info.Height / 2);
}
void cButton::Init(int x, int y, int w, int h)
{
	SetRect(&m_rt,
		m_Pos.x - m_Nomal->info.Width / 2+x,
		m_Pos.y - m_Nomal->info.Height / 2+y,
		m_Pos.x + m_Nomal->info.Width / 2-w,
		m_Pos.y + m_Nomal->info.Height / 2-h);
} 
bool cButton::isOver()
{
	POINT pt;
	pt = INPUTMANAGER->GetMousePos();
	if (PtInRect(&m_rt, pt))
		return true;
	else
		return false;
}
bool cButton::Update()
{
	m_MousePos = INPUTMANAGER->GetMousePos();
	if (b_Click) {
		if (INPUTMANAGER->MouseLUp() && isOver()) {

			FMOD.PlayEF("Button");
			return true;
		}
		else
			b_Click = false;
	}

	if (isOver()) {
		b_OnCursor = true;
		if (INPUTMANAGER->MouseLPress()) {
			b_Click = true;
		} 
		else {
			b_Click = false;
		}
	}
	else
		b_OnCursor = false;

	return false;
}

void cButton::Render()
{
	if (b_Click) {
		IMAGEMANAGER->CenterRender(m_Click, m_Pos.x, m_Pos.y, 1);
	}
	else if (b_OnCursor) {
		IMAGEMANAGER->CenterRender(m_OnCursor, m_Pos.x, m_Pos.y, 1);
	}
	else
		IMAGEMANAGER->CenterRender(m_Nomal, m_Pos.x, m_Pos.y, 1);
}

void cButton::Release()
{
}

