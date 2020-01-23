#pragma once
#include "singleton.h" 
// 텍스쳐의 정보를 담는 구조체 
// 구조체도 클래스와 같이 생성자, 파괴자를 사용 가능하며 맴버 함수도 넣을수 있다.

struct texture {

	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		: texturePtr(texturePtr), info(info) {}

	void Render(float x, float y, float size = 1.0);
	void CenterRender(float x, float y, float size = 1.0);

	void Render(float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

class cImageManager :
	public singleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite;  
	map<string, texture*> m_images;

public:

	vector<texture*> MakeVecTexture(const string& key);

	cImageManager();
	virtual ~cImageManager();

	void Render(texture* texturePtr, float x, float y, float size);
	void CropRender(texture* texturePtr, float x, float y, const RECT* a);
	void ScailRender(texture* texturePtr, float x, float y, float xsize, float ysize);
	void CenterRender(texture* texturePtr, float x, float y, float rot);

	void Render(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)); 
	void ScailCenterRender(texture* texturePtr, float x, float y, float xsize,float ysize, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)); 

	 
	texture* AddImage(const string& key, const string& path);
	texture* FindImage(const string& key);

	// sprite 처리 부분
	void Begin() { if (m_sprite) m_sprite->Begin(D3DXSPRITE_ALPHABLEND); }
	void End() { if (m_sprite) m_sprite->End(); }
	void OnResetDevice() { if (m_sprite) m_sprite->OnResetDevice(); }
	void OnLostDevice() { if (m_sprite) m_sprite->OnLostDevice(); } 

private:
	LPD3DXFONT m_Font50;
	LPD3DXFONT m_Font70;
	LPD3DXFONT m_Font100;
	LPD3DXFONT m_Font150;
public:
	void sDrawText(float x, float y, const string& str, int size, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

}; 
class cAnimation {
public:
	cAnimation(string Key, float fDelay, bool bLoop);
	~cAnimation();
private:
	vector<texture*> m_Texture;

	bool m_bLoop;
	bool m_bActive;
	int m_iCurFrame;

	int m_PMaxFrame;  

	float m_fDelay;
	float m_fTime = 0.f;
	CHARACTER_STATE m_pState;
public:
	bool Update();

	void Render(float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender( float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

	bool IsActive() { return m_bActive; }
	void SetActive(bool Active) { m_bActive = Active; }
	void setCurFrame(int n) { m_iCurFrame = n; }
	int GetFrame() { return m_iCurFrame; }
	void SetFrame(int Frame) { m_iCurFrame = Frame; }
	void SetPState(CHARACTER_STATE state) { m_pState = state; }
	CHARACTER_STATE GetPState() { return m_pState; }
};
#define IMAGEMANAGER cImageManager::GetInstance()

#define FONTMANAGER cImageManager::GetInstance()