#pragma once
#include "cWindow.h"
class cWndOption :public cWindow
{
private:
	cButton* m_Music;
	cButton* m_Credits;
public:
	cWndOption();
	~cWndOption();
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Release() override;

	bool getClickX() { return isClick_X; }
	void setClickX(bool click) { isClick_X = click; }
};

