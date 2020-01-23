#pragma once
class cFps
{
public:
	cFps();
	~cFps();
	bool Timer(float time);
	void SetStartTime();
	void Animation(const string& img, float x, float y, float size,float rot,int sheet, float frame);
private:
	DWORD m_NowTime;
	DWORD m_StartTime;
};

