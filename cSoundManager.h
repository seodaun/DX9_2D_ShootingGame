#pragma once
#define I (int)
#include<iostream>
#include<Windows.h>
#include <conio.h>
#include<vector>
#include<map>
enum class FMOD_ERR { NONE, OVERLAP, N_EXIST, ALREADY_RUNNING, NOT_RUNNING };
// FMODSound �޼ҵ尡 ��ȯ�ϴ� �����α׿� ���� ������
// �ƹ��͵� �ƴ�, ���̵� �ߺ�, ���� ���̵�, �̹� ������, �������� �ƴ�
enum class FMOD_LIST : int { BGM, EFFECT, MAX };

#include"FMOD/inc/fmod.h"
#pragma comment(lib,"FMOD/lib/fmodex_vc.lib")
using namespace std;

class CFMODSound
{
public: // ���������� ����ϰ� �� �޼ҵ��
	FMOD_ERR AddBGSound(const string& id, const string& filepath);
	//������� �߰�      (���� ���̵�, ���� ���� �ּ�)
	FMOD_ERR AddEFSound(const string& id, const string& filepath);
	//ȿ���� �߰�	    (���� ���̵�, ���� ���� �ּ�)
	FMOD_ERR PlayEF(const string& id);
	//ȿ���� ���   (���� ���̵�)
	FMOD_ERR PlayBG(const string& id);
	//������� ��� (���� ���̵�)
	FMOD_ERR StopBG(const string& id);
	//������� ���� (���� ���̵�)

public:
	vector<string> getEffectSoundList() { return m_vecSoundList[I FMOD_LIST::EFFECT]; }
	vector<string> getBgmSoundList() { return m_vecSoundList[I FMOD_LIST::BGM]; }

	void Release();
	void Update();

private:
	FMOD_SYSTEM* m_pSystem;

private: // SOUND
	map<string, FMOD_SOUND*> m_mapBGSound;
	map<string, FMOD_SOUND*> m_mapEFSound;

private:
	map<string, float> m_mapEFVol;
	map<string, float> m_mapBGVol;

private: // CHANNEL
	map<string, FMOD_CHANNEL*> m_mapBGChannel;
	map<string, bool>		   m_mapBGState;

private:
	vector<string> m_vecSoundList[2];

public:
	CFMODSound(void);
	~CFMODSound(void);
};

