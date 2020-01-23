#pragma once
#define I (int)
#include<iostream>
#include<Windows.h>
#include <conio.h>
#include<vector>
#include<map>
enum class FMOD_ERR { NONE, OVERLAP, N_EXIST, ALREADY_RUNNING, NOT_RUNNING };
// FMODSound 메소드가 반환하는 에러로그에 관한 열거형
// 아무것도 아님, 아이디 중복, 없는 아이디, 이미 실행중, 실행중이 아님
enum class FMOD_LIST : int { BGM, EFFECT, MAX };

#include"FMOD/inc/fmod.h"
#pragma comment(lib,"FMOD/lib/fmodex_vc.lib")
using namespace std;

class CFMODSound
{
public: // 실질적으로 사용하게 될 메소드들
	FMOD_ERR AddBGSound(const string& id, const string& filepath);
	//배경음악 추가      (음원 아이디, 음원 파일 주소)
	FMOD_ERR AddEFSound(const string& id, const string& filepath);
	//효과음 추가	    (음원 아이디, 음원 파일 주소)
	FMOD_ERR PlayEF(const string& id);
	//효과음 출력   (음원 아이디)
	FMOD_ERR PlayBG(const string& id);
	//배경음악 출력 (음원 아이디)
	FMOD_ERR StopBG(const string& id);
	//배경음악 멈춤 (음원 아이디)

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

