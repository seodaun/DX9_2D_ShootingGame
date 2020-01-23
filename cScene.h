#pragma once  

class cScene abstract
{
public:
	cScene();
	virtual ~cScene();

	// 맴버 함수에 PURE이 들어가면 상속받은 클래스에서 override 로 재정의.
	// ex) virtual void Init() override;

	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;
};

