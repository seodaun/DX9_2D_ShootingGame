#pragma once
#include "cScene.h"   
class cStage_1;
class cStage_2;
class cStage_3;
class cButton;
class cInGameScene :
	public cScene
{
private:  
	cStage_1* m_stage_1;
	cStage_2* m_stage_2;
	cStage_3* m_stage_3;
	 
	cButton* m_back;
	cButton* m_restart;
	cButton* m_continue;
private: 
	int m_stage;
	bool bPause=false;
	bool binit = false;
public:
	cInGameScene();
	virtual ~cInGameScene();

	virtual void Init()	override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};


 