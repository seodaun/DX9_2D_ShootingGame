#pragma once
class cButton
{
private:
	texture* m_Nomal;
	texture* m_OnCursor;
	texture* m_Click;

	POINT m_Pos;
	POINT m_MousePos;
	RECT m_rt;

	bool b_OnCursor;
	bool b_Click;
public:
	cButton(int x, int y, const string& key);

	void Init();
	void Init(int x,int y,int w, int h);
	bool Update();
	void Render();
	void Release();

	bool isOver();
};

