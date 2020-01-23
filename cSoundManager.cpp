#include "DXUT.h"
#include "cSoundManager.h"

FMOD_ERR CFMODSound::AddBGSound(const string& id, const string& filepath)
{
	if (m_mapBGSound.count(id) || m_mapBGChannel.count(id))
		return FMOD_ERR::OVERLAP;
	FMOD_SOUND* temp_sound;
	FMOD_System_CreateSound(m_pSystem, filepath.c_str(), FMOD_LOOP_NORMAL, 0, &temp_sound);
	m_mapBGSound.insert(make_pair(id, temp_sound));
	m_mapBGChannel.insert(make_pair(id, nullptr));
	m_mapBGState.insert(make_pair(id, false));
	m_mapBGVol.insert(make_pair(id, 1.0f));
	m_vecSoundList[I FMOD_LIST::BGM].push_back(id);
	return FMOD_ERR::NONE;
}

FMOD_ERR CFMODSound::AddEFSound(const string& id, const string& filepath)
{
	if (m_mapEFSound.count(id)) {
		return FMOD_ERR::OVERLAP;
	}
	FMOD_SOUND* temp_sound;
	FMOD_System_CreateSound(m_pSystem, filepath.c_str(), FMOD_DEFAULT, 0, &temp_sound);
	m_mapEFSound.insert(make_pair(id, temp_sound));
	m_mapEFVol.insert(make_pair(id, 1.0f));
	m_vecSoundList[I FMOD_LIST::BGM].push_back(id);
	return FMOD_ERR::NONE;
}

FMOD_ERR CFMODSound::PlayEF(const string& id)
{
	if (!m_mapEFSound.count(id)) {
		return FMOD_ERR::N_EXIST;
	}
	FMOD_SOUND* temp_sound = m_mapEFSound.find(id)->second;
	FMOD_CHANNEL* temp_channel;
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, temp_sound, 0, &temp_channel);
	FMOD_Channel_SetVolume(temp_channel, m_mapEFVol.find(id)->second);
	return FMOD_ERR::NONE;
}

FMOD_ERR CFMODSound::PlayBG(const string& id)
{
	if (!m_mapBGSound.count(id)) {
		return FMOD_ERR::N_EXIST;
	}
	if (m_mapBGState.find(id)->second == true) {
		return FMOD_ERR::ALREADY_RUNNING;
	}
	m_mapBGState.find(id)->second = true;
	FMOD_SOUND* temp_sound = m_mapBGSound.find(id)->second;
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, temp_sound, 0, &m_mapBGChannel.find(id)->second);
	FMOD_Channel_SetVolume(m_mapBGChannel.find(id)->second
		, m_mapBGVol.find(id)->second);
	return FMOD_ERR::NONE;
}

FMOD_ERR CFMODSound::StopBG(const string& id)
{
	if (!m_mapBGSound.count(id)) {
		return FMOD_ERR::N_EXIST;
	}
	if (m_mapBGState.find(id)->second == false) {
		return FMOD_ERR::NOT_RUNNING;
	}
	m_mapBGState.find(id)->second = false;
	FMOD_Channel_Stop(m_mapBGChannel.find(id)->second);
	return FMOD_ERR::NONE;
}

void CFMODSound::Release()
{
	for (auto i : m_vecSoundList[I FMOD_LIST::BGM]) {
		if (m_mapBGSound.count(i))
			FMOD_Sound_Release(m_mapBGSound.find(i)->second);
	}
	for (auto i : m_vecSoundList[I FMOD_LIST::EFFECT]) {
		if (m_mapEFSound.count(i))
			FMOD_Sound_Release(m_mapEFSound.find(i)->second);
	}
}

void CFMODSound::Update()
{
	if (!m_pSystem)
		FMOD_System_Update(m_pSystem);
}

CFMODSound::CFMODSound(void)
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 2048, FMOD_INIT_NORMAL, NULL);
}

CFMODSound::~CFMODSound(void)
{
	Release();
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}
