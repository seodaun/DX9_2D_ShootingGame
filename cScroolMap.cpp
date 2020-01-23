#include "DXUT.h"
#include "cScroolMap.h"


cScroolMap::cScroolMap(string background)
	:m_scrool(0)
{
	m_backGround = IMAGEMANAGER->FindImage(background);
}

cScroolMap::~cScroolMap()
{
}

void cScroolMap::Update(float speed)
{
	m_scrool += speed * DXUTGetElapsedTime();
}

void cScroolMap::Render()
{
	//반복되는 백그라운드 이미지를 예시로 사용할것임
	float renderPos = (int)m_scrool % m_backGround->info.Width;
	m_backGround->Render(m_backGround->info.Width - renderPos, 0, 1);//이어주는 화면
	m_backGround->Render(-renderPos, 0, 1);
}
