#pragma once

class cSound abstract
{
public:
	cSound();
	virtual ~cSound();

	// �ɹ� �Լ��� PURE�� ���� ��ӹ��� Ŭ�������� override �� ������.
	// ex) virtual void Init() override;

	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;
};

