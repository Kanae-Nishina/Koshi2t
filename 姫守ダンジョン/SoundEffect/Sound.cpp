#include "Sound.h"


map<string, int> SE_iSoundIndex;//SE�ۊǌ�
map<string, int> Normal_ATK;
map<string, int> Special_ATK;
map<string, int> Damage;
map<string, int> Damage_HIT;
map<string, int> Dead;
map<string, int> bgms;
map<string, int> over_SE;

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

void Sound::BGM_play(string BGM_mode)
{
	PlaySound(bgms[BGM_mode]);//�^�C�g��BGM
}

void Sound::BGM_stop(string BGM_mode)
{
	m_pSourceVoice[bgms[BGM_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
}

void Sound::SE_play(string SE_mode)
{
	PlaySound(Normal_ATK[SE_mode]);//�ʏ�U��
	PlaySound(Special_ATK[SE_mode]);//����U��
	PlaySound(Damage[SE_mode]);//�_���[�W
	PlaySound(Damage_HIT[SE_mode]);//�_���[�W�q�b�g
	PlaySound(Dead[SE_mode]);//���񂾂Ƃ�
}

void Sound::SE_stop(/*int gamescene, */string SE_mode)
{
	m_pSourceVoice[Normal_ATK[SE_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
	m_pSourceVoice[Special_ATK[SE_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
	m_pSourceVoice[Damage[SE_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
	m_pSourceVoice[Damage_HIT[SE_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
	m_pSourceVoice[Dead[SE_mode]]->Stop(0, XAUDIO2_COMMIT_NOW);
}

void Sound::Run()
{
	m_iSoundCurrentIndex = 0;
	//�T�E���h�֘A�iXAudio2�j�̏�����
	InitSound();
	// BGM
	bgms["SENTOU"] = LoadSound("SoundEffect\\BGM\\dew21.wav");

	//SE//

	//============���m============//
	//�ʏ�U��
	Normal_ATK["S_NORMALATK"] = LoadSound("SoundEffect/SE/sword_sound/s_normal.wav");
	m_pSourceVoice[Normal_ATK["S_NORMALATK"]]->SetVolume(3.0f, 0);

	//����U��
	Special_ATK["S_SPECIAL"] = LoadSound("SoundEffect/SE/sword_sound/s_specialATK.wav");
	m_pSourceVoice[Special_ATK["S_SPECIAL"]]->SetVolume(3.0f, 0);

	//�_���[�W
	Damage["S_DAMAGE"] = LoadSound("SoundEffect/SE/sword_sound/sword_damagevoice.wav");
	m_pSourceVoice[Damage["S_DAMAGE"]]->SetVolume(3.0f, 0);

	//�_���[�W�q�b�g
	Damage_HIT["S_DAMAGE_HIT"] = LoadSound("SoundEffect/SE/sword_sound/sword_hit.wav");
	m_pSourceVoice[Damage_HIT["S_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//���S
	Dead["S_DEAD"] = LoadSound("SoundEffect/SE/sword_sound/sword_dethvoice.wav");
	m_pSourceVoice[Dead["S_DEAD"]]->SetVolume(3.0f, 0);
	
	//============���m============//
	//�ʏ�U��
	Normal_ATK["Sh_NORMALATK"] = LoadSound("SoundEffect/SE/shiled_sound/shield_attack.wav");
	m_pSourceVoice[Normal_ATK["Sh_NORMALATK"]]->SetVolume(2.0f, 0);

	//����U��
	Special_ATK["Sh_SPECIAL"] = LoadSound("SoundEffect/SE/shiled_sound/shiled_SPwalk.wav");
	m_pSourceVoice[Special_ATK["Sh_SPECIAL"]]->SetVolume(5.0f, 0);

	//�_���[�W
	Damage["Sh_DAMAGE"] = LoadSound("SoundEffect/SE/shiled_sound/shield_damagevoice.wav");
	m_pSourceVoice[Damage["Sh_DAMAGE"]]->SetVolume(5.0f, 0);

	//�_���[�W�q�b�g
	Damage_HIT["Sh_DAMAGE_HIT"] = LoadSound("SoundEffect/SE/shiled_sound/shiled_hit.wav");
	m_pSourceVoice[Damage_HIT["Sh_DAMAGE_HIT"]]->SetVolume(1.0f, 0);

	//���S
	Dead["Sh_DEAD"] = LoadSound("SoundEffect/SE/shiled_sound/shiled_dethvoice.wav");
	m_pSourceVoice[Dead["Sh_DEAD"]]->SetVolume(3.0f, 0);

	//============�����m============//
	//�ʏ�U��
	Normal_ATK["M_NORMALATK"] = LoadSound("SoundEffect/SE/magic_sound/magic_attack.wav");
	m_pSourceVoice[Normal_ATK["M_NORMALATK"]]->SetVolume(2.0f, 0);

	//����U��
	Special_ATK["M_SPECIAL"] = LoadSound("SoundEffect/SE/magic_sound/magic_charge.wav");
	m_pSourceVoice[Special_ATK["M_SPECIAL"]]->SetVolume(5.0f, 0);

	//�_���[�W
	Damage["M_DAMAGE"] = LoadSound("SoundEffect/SE/magic_sound/magic_damagevoice.wav");
	m_pSourceVoice[Damage["M_DAMAGE"]]->SetVolume(3.0f, 0);

	//�_���[�W�q�b�g
	Damage_HIT["M_DAMAGE_HIT"] = LoadSound("SoundEffect/SE/magic_sound/magic_hit.wav");
	m_pSourceVoice[Damage_HIT["M_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//���S
	Dead["M_DEAD"] = LoadSound("SoundEffect/SE/magic_sound/magic_hit.wav");
	m_pSourceVoice[Dead["M_DEAD"]]->SetVolume(3.0f, 0);

	//============���e�m============//
	//�ʏ�U��
	Normal_ATK["B_NORMALATK"] = LoadSound("SoundEffect/SE/bomb_sound/bomb_hit.wav");
	m_pSourceVoice[Normal_ATK["B_NORMALATK"]]->SetVolume(2.0f, 0);

	//����U��
	Special_ATK["B_SPECIAL"] = LoadSound("SoundEffect/SE/bomb_sound/pui.wav");
	m_pSourceVoice[Special_ATK["B_SPECIAL"]]->SetVolume(0.5f, 0);

	//�_���[�W
	Damage["B_DAMAGE"] = LoadSound("SoundEffect/SE/bomb_sound/bomb_damage.wav");
	m_pSourceVoice[Damage["B_DAMAGE"]]->SetVolume(3.0f, 0);

	//�_���[�W�q�b�g
	Damage_HIT["B_DAMAGE_HIT"] = LoadSound("SoundEffect/SE/bomb_sound/bomb_hit.wav");
	m_pSourceVoice[Damage_HIT["B_DAMAGE_HIT"]]->SetVolume(3.0f, 0);

	//���S
	Dead["B_DEAD"] = LoadSound("SoundEffect/SE/bomb_sound/bomb_deth.wav");
	m_pSourceVoice[Dead["B_DEAD"]]->SetVolume(3.0f, 0);

	/*Special_ATK["B_SPECIAL"] = LoadSound("SoundEffect/SE/bomb_sound/onara.wav");
	m_pSourceVoice[Special_ATK["B_SPECIAL"]]->SetVolume(5.0f, 0);*/


	/*bgms["PLAY"] = LoadSound("SoundEffect\\BGM\\9V.wav");*/
	// SE
	// �^�C�g��
	//SE_iSoundIndex["TIPE"] = LoadSound("SoundEffect\\SE\\key.wav");
	//SE_iSoundIndex["ENTER"] = LoadSound("SoundEffect\\SE\\Enter.wav");
	//SE_iSoundIndex["CURSOR"] = LoadSound("SoundEffect\\SE\\cursor.wav");
	// �v���C��
	/*main_SE["COIN"] = LoadSound("SoundEffect\\SE\\coin2.wav");
	m_pSourceVoice[main_SE["COIN"]]->SetVolume(0.3f, 0);
	main_SE["JUMP"] = LoadSound("SoundEffect\\SE\\Jump.wav");
	m_pSourceVoice[main_SE["JUMP"]]->SetVolume(2.0f, 0);
	main_SE["LAND"] = LoadSound("SoundEffect\\SE\\landing.wav");
	m_pSourceVoice[main_SE["LAND"]]->SetVolume(2.0f, 0);
	main_SE["CHECK"] = LoadSound("SoundEffect\\SE\\checkpoint.wav");
	m_pSourceVoice[main_SE["CHECK"]]->SetVolume(5.0f, 0);
	main_SE["SPIN"] = LoadSound("SoundEffect\\SE\\roll1.wav");*/
	//main_SE["DESTROY_ERROR"]=LoadSound("SoundEffect\\SE\\erorrend.wav");
	//m_pSourceVoice[main_SE["DESTROY_ERROR"]]->SetVolume(2.0f, 0);
	//// �Q�[���I�[�o�[
	//over_SE["ERROR"] = LoadSound("SoundEffect\\SE\\cancel2.wav");
	//m_pSourceVoice[over_SE["ERROR"]]->SetVolume(2.0f, 0);
	//over_SE["MAINERROR"] = LoadSound("SoundEffect\\SE\\cancel1.wav");
	//m_pSourceVoice[over_SE["MAINERROR"]]->SetVolume(2.0f, 0);

	////�A�v���P�[�V�����̏I��
}

int Sound::LoadSound(char* szFileName)
{
	static int iIndex = -1;
	iIndex++;
	HMMIO			hMmio		= NULL;	//Windows�}���`���f�B�AAPI�̃n���h��(Windows�}���`���f�B�AAPI��WAV�t�@�C���֌W�̑���p��API)
	DWORD			dwWavSize	= 0;	//WAV�t�@�C�����@WAV�f�[�^�̃T�C�Y�iWAV�t�@�C����WAV�f�[�^�Ő�߂��Ă���̂ŁA�قڃt�@�C���T�C�Y�Ɠ���j
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

void  Sound::PlaySound(int iSoundIndex)
{
	m_pSourceVoice[iSoundIndex]->Stop(0, 1);
	m_pSourceVoice[iSoundIndex]->FlushSourceBuffers();
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = m_pWavBuffer[iSoundIndex];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = m_dwWavSize[iSoundIndex];
	if (FAILED(m_pSourceVoice[iSoundIndex]->SubmitSourceBuffer(&buffer)))
	{
		MessageBox(0, L"�\�[�X�{�C�X�ɃT�u�~�b�g���s", 0, MB_OK);
		return;
	}
	//m_pSourceVoice[iSoundIndex]->
	m_pSourceVoice[iSoundIndex]->Start(0, XAUDIO2_COMMIT_NOW);
}

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
