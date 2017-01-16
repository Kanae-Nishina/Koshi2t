#pragma once
#include <xaudio2.h>
#include <map>
#include <vector>
#include <string>
#include "../Origin.h"
#define MAX_WAV 100 //WAV�T�E���h�ő吔


using namespace std;

class Sound
{
private:
	Sound();
	~Sound();

public:
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;
	Sound(Sound&&) = delete;
	Sound& operator=(Sound&&) = delete;

	static Sound& getInstance()
	{
		static Sound inst;
		return inst;
	}

	HRESULT InitSound();
	int LoadSound(char* szFileName);
	void  PlaySound(int iSoundIndex);
	void Run();
	IXAudio2* m_pXAudio2;
	IXAudio2MasteringVoice* m_pMasteringVoice;
	IXAudio2SourceVoice* m_pSourceVoice[MAX_WAV];
	BYTE* m_pWavBuffer[MAX_WAV];					//�g�`�f�[�^�i�t�H�[�}�b�g�����܂܂Ȃ��A�����ɔg�`�f�[�^�̂݁j
	DWORD m_dwWavSize[MAX_WAV];						//�g�`�f�[�^�̃T�C�Y
	int m1_iSoundIndex[10];							//����ǂݍ��މ��̔ԍ�
	int m_iSoundCurrentIndex;						//���̌��݂̍Đ��ԍ�
	bool bgm_flg;									//BGM���Ȃ��Ă邩
	
	void SE_play(string SE_mode);		// SE�Đ�
	void SE_stop(string SE_mode);	// SE��~
	void BGM_play(string BGM_mode);					// BGM�Đ�
	void BGM_stop(string BGM_mode);					// BGM��~


};
