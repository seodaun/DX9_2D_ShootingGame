#include "DXUT.h"
#include "cImgManager.h"


// texture

void texture::Render(float x, float y, float size)
{
	IMAGEMANAGER->Render(this, x, y, size);
}

void texture::CenterRender(float x, float y, float size)
{
	IMAGEMANAGER->CenterRender(this, x, y, size);
}

void texture::Render(float x, float y, float size, float rot, D3DCOLOR color)
{
	IMAGEMANAGER->Render(this, x, y, size, rot, color);
}

void texture::CenterRender(float x, float y, float size, float rot, D3DCOLOR color)
{
	IMAGEMANAGER->CenterRender(this, x, y, size, rot, color);
}
vector<texture*> cImageManager::MakeVecTexture(const string& key)
{ 
	vector<texture*> m_vTexture;
	for (int i = 0; ; i++)
	{
		char Key[100];
		sprintf(Key, "%s_%d", key.c_str(), i);
		if (IMAGEMANAGER->FindImage(Key) != nullptr)
			m_vTexture.push_back(IMAGEMANAGER->FindImage(Key));
		else
			break;
	} 
	return m_vTexture;
}
cImageManager::cImageManager()
{
	D3DXCreateSprite(g_device, &m_sprite);
	D3DXCreateFont(g_device, 50, 0, 10, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &m_Font50);
	D3DXCreateFont(g_device, 70, 0, 10, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &m_Font70);
	D3DXCreateFont(g_device, 100, 0, 10, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &m_Font100);
	D3DXCreateFont(g_device, 150, 0, 10, 1, FALSE, HANGUL_CHARSET, 0, 0, 0, TEXT("Fixedsys"), &m_Font150);
}

cImageManager::~cImageManager()
{
	for (auto iter : m_images) {
		SAFE_RELEASE(iter.second->texturePtr);
		SAFE_DELETE(iter.second);
	}    
	m_images.clear();

	SAFE_RELEASE(m_sprite);
	SAFE_RELEASE(m_Font50);
	SAFE_RELEASE(m_Font70);
	SAFE_RELEASE(m_Font100);
	SAFE_RELEASE(m_Font150);
}

void cImageManager::Render(texture* texturePtr, float x, float y, float size)
{
	if (texturePtr) {
		D3DXMATRIX mtT, mtW, mtS;
		D3DXMatrixScaling(&mtS, size, size, 1); //이미지 크기 
		D3DXMatrixTranslation(&mtT, x, y, 0.f); //(돌아가는 위치) 매트릭승에 좌표 설정 
		mtW = mtS * mtT;
		m_sprite->SetTransform(&mtW);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cImageManager::CropRender(texture* texturePtr, float x, float y, const RECT* a)
{
	if (texturePtr) {
		D3DXMATRIX mtT, mtW, mtS;
		D3DXMatrixScaling(&mtS, 1, 1, 1); //이미지 크기 
		D3DXMatrixTranslation(&mtT, x, y, 0.f); //(돌아가는 위치) 매트릭승에 좌표 설정 
		mtW = mtS * mtT;
		m_sprite->SetTransform(&mtW);
		m_sprite->Draw(texturePtr->texturePtr, a, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cImageManager::ScailRender(texture* texturePtr, float x, float y, float xsize, float ysize)
{
	if (texturePtr) {
		D3DXMATRIX mtT, mtW, mtS;
		D3DXMatrixScaling(&mtS, xsize, ysize, 1); //이미지 크기 
		D3DXMatrixTranslation(&mtT, x, y, 0.f); //(돌아가는 위치) 매트릭승에 좌표 설정 
		mtW = mtS * mtT;
		m_sprite->SetTransform(&mtW);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cImageManager::CenterRender(texture* texturePtr, float x, float y, float size)
{
	if (texturePtr) {
		D3DXMATRIX mtT, mtT1, mtW, mtS, mtR;
		D3DXMatrixScaling(&mtS, size, size, 1); //이미지 크기 
		D3DXMatrixTranslation(&mtT, x, y, 0.f); //(돌아가는 위치) 매트릭승에 좌표 설정
		D3DXMatrixTranslation(&mtT1, -(texturePtr->info.Width / 2.f), -(texturePtr->info.Height / 2.f), 0.f);
		mtW = mtS * (mtT1 * mtT);
		m_sprite->SetTransform(&mtW);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cImageManager::Render(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color)
{
	if (texturePtr) {
		D3DXMATRIX mtT, mat, mtS, mtR;
		D3DXMatrixScaling(&mtS, size, size, 1); //이미지 크기 
		D3DXMatrixTranslation(&mtT, x, y, 0.f); //(돌아가는 위치) 매트릭승에 좌표 설정 
		D3DXMatrixRotationZ(&mtR, D3DXToRadian(rot));
		mat = (mtS * mtR) * mtT;
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cImageManager::CenterRender(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color)
{
	if (texturePtr) {
		D3DXMATRIX mat, mtT, mtT1, mtS, mtR;
		D3DXMatrixScaling(&mtS, size, size, 1);
		D3DXMatrixTranslation(&mtT, x, y, 0.f);
		D3DXMatrixTranslation(&mtT1, -(texturePtr->info.Width / 2.f), -(texturePtr->info.Height / 2.f), 0.f);
		D3DXMatrixRotationZ(&mtR, D3DXToRadian(rot));
		mat = mtT1 * (mtS * mtR) * mtT;
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cImageManager::ScailCenterRender(texture* texturePtr, float x, float y, float xsize, float ysize, float rot, D3DCOLOR color)
{
	if (texturePtr) {
		D3DXMATRIX mat, mtT, mtT1, mtS, mtR;
		D3DXMatrixScaling(&mtS, xsize, ysize, 1);
		D3DXMatrixTranslation(&mtT, x, y, 0.f);
		D3DXMatrixTranslation(&mtT1, -(texturePtr->info.Width / 2.f), -(texturePtr->info.Height / 2.f), 0.f);
		D3DXMatrixRotationZ(&mtR, D3DXToRadian(rot));
		mat = mtT1 * (mtS * mtR) * mtT;
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}


texture* cImageManager::AddImage(const string& key, const string& path)
{
	auto find = m_images.find(key);
	if (find != m_images.end())
		return find->second;
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texturePtr;

	if (D3DXCreateTextureFromFileExA(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK) {
		texture* text = new texture(texturePtr, info);
		m_images.insert(make_pair(key, text));
		return text;
	}
	return nullptr;
}

texture* cImageManager::FindImage(const string& key)
{
	auto find = m_images.find(key);
	if (find == m_images.end()) {
		//DEBUG_LOG(key + "이미지를 찾지 못햇어");
		return nullptr;
	}

	return find->second;
}

void cImageManager::sDrawText(float x, float y, const string& str, int size, D3DXCOLOR color)
{
	D3DXMATRIX mat;
	RECT rc = { 0 };
	D3DXMatrixTranslation(&mat, x, y, 0);

	m_sprite->SetTransform(&mat);
	switch (size) {
	case 50:
		m_Font50->DrawTextA(m_sprite, str.c_str(), str.size(), &rc, DT_NOCLIP, color);
		break;
	case 70:
		m_Font70->DrawTextA(m_sprite, str.c_str(), str.size(), &rc, DT_NOCLIP, color);
		break;
	case 100:
		m_Font100->DrawTextA(m_sprite, str.c_str(), str.size(), &rc, DT_NOCLIP, color);
		break;
	case 150:
		m_Font150->DrawTextA(m_sprite, str.c_str(), str.size(), &rc, DT_NOCLIP, color);
		break;
	default:
		DEBUG_LOG("지원하는 텍스트 크기가 없습니다 . 50, 70, 100, 150 의 값중 하나를 고르세요");
		break;
	}
	return;
}

cAnimation::cAnimation(string Key, float fDelay, bool bLoop)
	:m_fDelay(fDelay), m_bLoop(bLoop), m_bActive(true), m_fTime(0.f), m_iCurFrame(0)
{
	m_Texture = IMAGEMANAGER->MakeVecTexture(Key);
	m_PMaxFrame = m_Texture.size();
}
cAnimation::~cAnimation()
{
}

bool cAnimation::Update()
{
	int maxFrame = m_PMaxFrame;
	if (m_bActive)
	{
		if (m_fTime >= m_fDelay)
		{
			m_fTime = 0.f;
			m_iCurFrame++;
			if (m_iCurFrame >= maxFrame)
			{
				m_iCurFrame = 0;
				if (!m_bLoop)
					m_bActive = false;//반복안할경우
				return true;
			}
			return false;
		}
		else {
			m_fTime += DXUTGetElapsedTime();
			return false;
		}
	} 
}
void cAnimation::Render(float x, float y, float size, float rot, D3DCOLOR color)
{
	IMAGEMANAGER->Render(m_Texture[m_iCurFrame], x, y, size, rot, color);
}

void cAnimation::CenterRender( float x, float y, float size, float rot, D3DCOLOR color)
{
	IMAGEMANAGER->CenterRender(m_Texture[m_iCurFrame], x, y, size, rot, color);
}
