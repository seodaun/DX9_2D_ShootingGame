#pragma once
#include "singleton.h" 
// 씬들을 보관 , 현재 씬의 Update와 Render를 직접 처리해주는 클래스인
// cSceneManager를 정의했다.

class cScene;
class cSceneManager :
	public singleton<cSceneManager>
{
private:

	// map 자료형에 문자열과 cScene의 포인터를 사용해
	// 문자열로 씬을 추가/찾기가 가능하다.

	map<string, cScene*> m_scenes;

	cScene* nowScene;	// 현재 씬의 포인터
	cScene* nextScene;	// 다음 씬의 포인터

private:
	void Init();
	void Release();
public:
	cSceneManager() { Init(); }
	virtual ~cSceneManager() { Release(); }

	void Update();
	void Render();

	cScene* AddScene(const string& key, cScene* ptr);
	cScene* ChangeScene(const string& key);
};

#define SCENEMANAGER cSceneManager::GetInstance()