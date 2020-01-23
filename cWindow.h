#pragma once
class cButton;
class cWindow abstract
{
protected:
	bool isClick_X;
	cButton* m_X;
public:
	cWindow();
	virtual ~cWindow();

	virtual void Render() PURE;
	virtual void Update() PURE;
	virtual void Init() PURE;
	virtual void Release() PURE;
};

