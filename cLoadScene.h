#pragma once
#include "cScene.h"
// cScene 클래스를 상속받아 만든
// cLoadingScene 클래스.

// 이미지 로딩을 담당하는 씬이다.

class cLoadScene :
	public cScene
{
private:
	int m_NowLoad;
	int m_MaxLoad;
	struct strBun
	{
		string key;
		string path;
		int count = 0;
		strBun(const string& key, const string& path, int count = 0)
			:key(key), path(path), count(count) {};
	};
	vector<strBun> m_Load;

	void Load(const string& key, const string& path, int count = 0) {
		m_Load.push_back(strBun(key, path, count));
	}
public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init()	override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override; 
};

