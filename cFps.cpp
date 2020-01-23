#include "DXUT.h"
#include "cFps.h"
#include <Windows.h>
#include <string>
cFps::cFps()
{
}

cFps::~cFps()
{
}

bool cFps::Timer(float time)
{
	m_NowTime = timeGetTime();
	return m_NowTime >= m_StartTime+time ? true : false;
}

void cFps::SetStartTime()
{
	m_StartTime = timeGetTime();
}

void cFps::Animation(const string& img, float x, float y, float size, float rot, int sheet, float frame)
{ 
	static int i =0 ;
	if (Timer(frame)) {
		i++;
		SetStartTime();
	}
	else if (i == sheet) i = 0; 
	IMAGEMANAGER->CenterRender(IMAGEMANAGER->FindImage(img+"_"+to_string(i)), x, y, size, rot);
	
}
 