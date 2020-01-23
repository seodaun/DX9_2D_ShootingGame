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
	//�ݺ��Ǵ� ��׶��� �̹����� ���÷� ����Ұ���
	float renderPos = (int)m_scrool % m_backGround->info.Width;
	m_backGround->Render(m_backGround->info.Width - renderPos, 0, 1);//�̾��ִ� ȭ��
	m_backGround->Render(-renderPos, 0, 1);
}
