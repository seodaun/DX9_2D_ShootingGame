#pragma once
class cMainGame
{
public:
	cMainGame() {}
	~cMainGame() {}

	void Init();	// Init�� �ʱ�ȭ �Լ�
	void Update();	// Update�� �� �����Ӹ��� ȣ��Ǵ� �Լ�
	void Render();	// Render�� �׷��� ����� ����ϴ� �Լ�
	void Release();	// Release�� ���� �޸� �Ҵ��̳� ���� ����

	void OnLostDevice();
	void OnResetDevice();
};

