#pragma once
#include "cScene.h"
class cButton;
class cTitleScene : public cScene
{
public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	POINT mousepos;

private:
	cButton* m_StartBtn;
};

