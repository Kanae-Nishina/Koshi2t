//
//	@file	Sound.cpp
//	@brief	�T�E���h�Ǘ��N���X
//	@date	4���A1���C��
//	@author	�g�z��R
//	@note	���ɗp�ӂ���Ă����N���X��啝�ɕύX

#include "Sound.h"

map<string, int> SE_iSoundIndex;//SE�ۊǌ�

//=======================================================
//	�R���X�g���N�^
//=======================================================
Sound::Sound()
{
	ZeroMemory(this, sizeof(Sound));
	bgm_flg = true;
}

//=======================================================
//	�f�X�g���N�^
//=======================================================
Sound::~Sound()
{
	for (int i = 0; i<MAX_WAV; i++)
	{
		if (m_pSourceVoice[i]) m_pSourceVoice[i]->DestroyVoice();
	}
	for (int i = 0; i<MAX_WAV; i++) SAFE_DELETE(m_pWavBuffer[i]);
	SAFE_RELEASE(m_pXAudio2);
}

//
//	@brief				BGM�Đ�
//	@param(BGM_mode)	�Đ�����BGM��
void Sound::BGM_play(string BGM_mode)
{
	PlaySound(SE_iSoundIndex[BGM_mode],true);
}

//
//	@brief				BGM��~
//	@param(BGM_mode)	��~����BGM��
void Sound::BGM_stop(string BGM_mode)
{
	m_pSourceVoice[SE_iSoundIndex[BGM_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
}

//
//	@brief				SE�Đ�
//	@param(BGM_mode)	�Đ�����SE��
void Sound::SE_play(string SE_mode)
{
	PlaySound(SE_iSoundIndex[SE_mode],false);
}

//
//	@brief				SE��~
//	@param(BGM_mode)	��~����SE��
void Sound::SE_stop(string SE_mode)
{
	m_pSourceVoice[SE_iSoundIndex[SE_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
}

void Sound::Run()
{
	//�T�E���h�֘A�iXAudio2�j�̏�����
	InitSound();

	//BGM//
	SE_iSoundIndex["TITLE"] = LoadSound("Sound/SE/all_sound/Title.wav");
	SE_iSoundIndex["CHARACTERSELECT"] = LoadSound("Sound/SE/all_sound/select.wav");
	SE_iSoundIndex["SENTOU"] = LoadSound("Sound/SE/all_sound/game_Main.wav");
	SE_iSoundIndex["CLEAR"] = LoadSound("Sound/SE/all_sound/result.wav");
	SE_iSoundIndex["FAILED"] = LoadSound("Sound/SE/all_sound/game_Over.wav");
	
	//SE//
	SE_iSoundIndex["DECISION_SE"] = LoadSound("Sound/SE/all_sound/decision.wav");
	m_pSourceVoice[SE_iSoundIndex["DECISION_SE"]]->SetVolume(3.0f, 0);

	//============���m============//
	//�ʏ�U��
	SE_iSoundIndex["S_NORMALATK"] = LoadSound("Sound/SE/sword_sound/s_normal.wav");
	m_pSourceVoice[SE_iSoundIndex["S_NORMALATK"]]->SetVolume(3.0f, 0);

	//����U��
	SE_iSoundIndex["S_SPECIAL"] = LoadSound("Sound/SE/sword_sound/s_specialATK.wav");
	m_pSourceVoice[SE_iSoundIndex["S_SPECIAL"]]->SetVolume(3.0f, 0);

	//�_���[�W
	SE_iSoundIndex["S_DAMAGE"] = LoadSound("Sound/SE/sword_sound/sword_damagevoice.wav");
	m_pSourceVoice[SE_iSoundIndex["S_DAMAGE"]]->SetVolume(3.0f, 0);

	//�_���[�W�q�b�g
	SE_iSoundIndex["S_DAMAGE_HIT"] = LoadSound("Sound/SE/sword_sound/sword_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["S_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//���S
	SE_iSoundIndex["S_DEAD"] = LoadSound("Sound/SE/sword_sound/sword_dethvoice.wav");
	m_pSourceVoice[SE_iSoundIndex["S_DEAD"]]->SetVolume(3.0f, 0);

	//============���m============//
	//�ʏ�U��
	SE_iSoundIndex["Sh_NORMALATK"] = LoadSound("Sound/SE/shiled_sound/shield_attack.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_NORMALATK"]]->SetVolume(2.0f, 0);

	//����U��
	SE_iSoundIndex["Sh_SPECIAL"] = LoadSound("Sound/SE/shiled_sound/shiled_SPwalk.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_SPECIAL"]]->SetVolume(5.0f, 0);

	//�_���[�W
	SE_iSoundIndex["Sh_DAMAGE"] = LoadSound("Sound/SE/shiled_sound/shield_damagevoice.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_DAMAGE"]]->SetVolume(5.0f, 0);

	//�_���[�W�q�b�g
	SE_iSoundIndex["Sh_DAMAGE_HIT"] = LoadSound("Sound/SE/shiled_sound/shiled_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_DAMAGE_HIT"]]->SetVolume(1.0f, 0);

	//���S
	SE_iSoundIndex["Sh_DEAD"] = LoadSound("Sound/SE/shiled_sound/shiled_dethvoice.wav");
	m_pSourceVoice[SE_iSoundIndex["Sh_DEAD"]]->SetVolume(3.0f, 0);

	//============�����m============//
	//�ʏ�U��
	SE_iSoundIndex["M_NORMALATK"] = LoadSound("Sound/SE/magic_sound/magic_attack.wav");
	m_pSourceVoice[SE_iSoundIndex["M_NORMALATK"]]->SetVolume(2.0f, 0);

	//����U��
	SE_iSoundIndex["M_SPECIAL"] = LoadSound("Sound/SE/magic_sound/magic_charge.wav");
	m_pSourceVoice[SE_iSoundIndex["M_SPECIAL"]]->SetVolume(5.0f, 0);

	//�_���[�W
	SE_iSoundIndex["M_DAMAGE"] = LoadSound("Sound/SE/magic_sound/magic_damagevoice.wav");
	m_pSourceVoice[SE_iSoundIndex["M_DAMAGE"]]->SetVolume(3.0f, 0);

	//�_���[�W�q�b�g
	SE_iSoundIndex["M_DAMAGE_HIT"] = LoadSound("Sound/SE/magic_sound/magic_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["M_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//���S
	SE_iSoundIndex["M_DEAD"] = LoadSound("Sound/SE/magic_sound/magic_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["M_DEAD"]]->SetVolume(3.0f, 0);

	//�`���[�W
	SE_iSoundIndex["M_CHARGE"] = LoadSound("Sound/SE/magic_sound/m_Charge.wav");
	m_pSourceVoice[SE_iSoundIndex["M_CHARGE"]]->SetVolume(3.0f, 0);

	//============���e�m============//
	//�ʏ�U��
	SE_iSoundIndex["B_NORMALATK"] = LoadSound("Sound/SE/bomb_sound/bomb_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["B_NORMALATK"]]->SetVolume(2.0f, 0);

	//����U��
	SE_iSoundIndex["B_SPECIAL"] = LoadSound("Sound/SE/bomb_sound/pui.wav");
	m_pSourceVoice[SE_iSoundIndex["B_SPECIAL"]]->SetVolume(0.5f, 0);

	//�_���[�W
	SE_iSoundIndex["B_DAMAGE"] = LoadSound("Sound/SE/bomb_sound/bomb_damage.wav");
	m_pSourceVoice[SE_iSoundIndex["B_DAMAGE"]]->SetVolume(3.0f, 0);

	//�_���[�W�q�b�g
	SE_iSoundIndex["B_DAMAGE_HIT"] = LoadSound("Sound/SE/bomb_sound/bomb_hit.wav");
	m_pSourceVoice[SE_iSoundIndex["B_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//���S
	SE_iSoundIndex["B_DEAD"] = LoadSound("Sound/SE/bomb_sound/bomb_deth.wav");
	m_pSourceVoice[SE_iSoundIndex["B_DEAD"]]->SetVolume(3.0f, 0);

	//�`���[�W
	SE_iSoundIndex["B_CHARGE"] = LoadSound("Sound/SE/bomb_sound/b_Charge.wav");
	m_pSourceVoice[SE_iSoundIndex["B_CHARGE"]]->SetVolume(3.0f, 0);

	//============�P============//
	//���S
	SE_iSoundIndex["P_DEAD"] = LoadSound("Sound/SE/princess_sound/princessdamage.wav");

	//�N���A���s
	SE_iSoundIndex["P_FAILED"] = LoadSound("Sound/SE/princess_sound/princesslose.wav");

	//�N���A����
	SE_iSoundIndex["P_CLEAR"] = LoadSound("Sound/SE/princess_sound/princesswin.wav");

	//�h��
	SE_iSoundIndex["P_RES"] = LoadSound("Sound/SE/princess_sound/q_Resuscitation.wav");
	
	//����
	SE_iSoundIndex["P_SEAL"] = LoadSound("Sound/SE/princess_sound/q_Sealed.wav");

	//�X�e�[�W�N���A
	SE_iSoundIndex["P_STEGECLEAR"] = LoadSound("Sound/SE/princess_sound/game_Clear.wav");
}

//
//	@brief				���̓ǂݍ���
//	@param(szFileName)	�p�X
int Sound::LoadSound(char* szFileName)
{
	static int iIndex = -1;
	iIndex++;
	HMMIO			hMmio = NULL;	//Windows�}���`���f�B�AAPI�̃n���h��(Windows�}���`���f�B�AAPI��WAV�t�@�C���֌W�̑���p��API)
	DWORD			dwWavSize = 0;	//WAV�t�@�C�����@WAV�f�[�^�̃T�C�Y�iWAV�t�@�C����WAV�f�[�^�Ő�߂��Ă���̂ŁA�قڃt�@�C���T�C�Y�Ɠ���j
	WAVEFORMATEX*	pwfex;				//WAV�̃t�H�[�}�b�g ��j16�r�b�g�A44100Hz�A�X�e���I�Ȃ�
	MMCKINFO		ckInfo;				//�@�`�����N���
	MMCKINFO		riffckInfo;			// �ŏ㕔�`�����N�iRIFF�`�����N�j�ۑ��p
	PCMWAVEFORMAT	pcmWaveForm;

	hMmio = mmioOpenA(szFileName, NULL, MMIO_ALLOCBUF | MMIO_READ);	//WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	mmioDescend(hMmio, &riffckInfo, NULL, 0);						//�t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');					// �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g����
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);

	//�t�H�[�}�b�g��ǂݍ���
	mmioRead(hMmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
	pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(pwfex, &pcmWaveForm, sizeof(pcmWaveForm));
	pwfex->cbSize = 0;
	mmioAscend(hMmio, &ckInfo, 0);

	// WAV�t�@�C�����̉��f�[�^�̓ǂݍ���	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);		//�f�[�^�`�����N�ɃZ�b�g
	dwWavSize = ckInfo.cksize;
	m_pWavBuffer[iIndex] = new BYTE[dwWavSize];
	DWORD dwOffset = ckInfo.dwDataOffset;
	mmioRead(hMmio, (HPSTR)m_pWavBuffer[iIndex], dwWavSize);

	//�\�[�X�{�C�X�Ƀf�[�^���l�ߍ���	
	if (FAILED(m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[iIndex], pwfex)))
	{
		MessageBox(0, L"�\�[�X�{�C�X�쐬���s", 0, MB_OK);
		return E_FAIL;
	}
	m_dwWavSize[iIndex] = dwWavSize;
	return iIndex;
}

//
//	@brief				�Đ�
//	@param(iSoundIndex)	�Đ�����ԍ�
//	@param(loopflg)		���[�v�t���O
void  Sound::PlaySound(int iSoundIndex, bool loopflg)
{
	m_pSourceVoice[iSoundIndex]->Stop(0, 1);
	m_pSourceVoice[iSoundIndex]->FlushSourceBuffers();
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = m_pWavBuffer[iSoundIndex];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = m_dwWavSize[iSoundIndex];
	if (loopflg)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	if (FAILED(m_pSourceVoice[iSoundIndex]->SubmitSourceBuffer(&buffer)))
	{
		MessageBox(0, L"�\�[�X�{�C�X�ɃT�u�~�b�g���s", 0, MB_OK);
		return;
	}
	m_pSourceVoice[iSoundIndex]->Start(0, XAUDIO2_COMMIT_NOW);
}

//
//	@brief	������
HRESULT Sound::InitSound()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(XAudio2Create(&m_pXAudio2,0 )))
	{
		CoUninitialize();
		return E_FAIL;
	}
	if (FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice)))
	{
		CoUninitialize();
		return E_FAIL;
	}
	return S_OK;
}
