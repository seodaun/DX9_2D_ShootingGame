#pragma once
class cMainGame
{
public:
	cMainGame() {}
	~cMainGame() {}

	void Init();	// Init은 초기화 함수
	void Update();	// Update는 매 프레임마다 호출되는 함수
	void Render();	// Render는 그래픽 출력을 담당하는 함수
	void Release();	// Release는 각종 메모리 할당이나 값의 해제

	void OnLostDevice();
	void OnResetDevice();
};

