#include "DXUT.h"
#include "cSceneManager.h" 
#include "cScene.h"
 
void cSceneManager::Init()
{
	nowScene = nullptr;
	nextScene = nullptr;
}

void cSceneManager::Release()
{
	if (nowScene)
		nowScene->Release();

	for (auto iter : m_scenes)
	{
		SAFE_DELETE(iter.second);
	}
	m_scenes.clear();
}

void cSceneManager::Update()
{
	if (nextScene) {

		if (nowScene)
			nowScene->Release();

		nextScene->Init();

		nowScene = nextScene;
		nextScene = nullptr;

	}

	if (nowScene)
		nowScene->Update();
}

void cSceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
}

cScene* cSceneManager::AddScene(const string& key, cScene* ptr)
{
	if (!ptr) return nullptr;

	auto find = m_scenes.find(key);

	if (find != m_scenes.end()) {
		return find->second;
	}

	m_scenes.insert(make_pair(key, ptr));
	return ptr;
}

cScene* cSceneManager::ChangeScene(const string& key)
{
	auto find = m_scenes.find(key);

	if (find == m_scenes.end()) {
		return nullptr;
	}

	nextScene = find->second;

	return nowScene;
}
