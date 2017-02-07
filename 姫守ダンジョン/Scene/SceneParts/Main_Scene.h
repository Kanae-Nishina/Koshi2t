//
//	@file	Main_Scene.h
//	@brief	���C���Q�[���V�[���N���X
//	@date	2016/11/08
//	@author	�m�ȍ��c
//	@author	�g�z��R(�G�t�F�N�g�EUI)

#pragma once
#include <vector>
#include <time.h>
//#include "./../../Read/XFileRead.h"
//#include "./../../Read/ParameterRead.h"
//#include "./../../Read/MotionRead.h"
#include "./../../Stage/Stage.h"
#include "./../../Charactor/Player/PlayerCommon.h"
#include "./../../Charactor/CharactorCreator.h"
#include "./../../Charactor/Enemy/EnemyJobManager.h"
#include "./../../Stage/SpawnManager.h"
#include "./../../Charactor/Princess.h"
#include "./../../Collision.h"
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/Title_Scene.h"
#include "./../SceneParts/Result_Scene.h"

#define UI_TIME 12 //���ԕ\���Ɏg�p����UI�̐�
#define SEMICOLON 10
#define ENEMY_MAX 50
#define FAILED_UI_POSY 350
#define FAILED_CHOICE_POSY 850

class Main_Scene :public Scene
{
private:
	TD_Graphics* uiStart_;
	TD_Graphics* uiFailed_;
	TD_Graphics* uiRetry_[2];
	TD_Graphics* uiBack_[2];
	TD_Graphics* uiHand_;
	TD_Graphics* uiTime_[UI_TIME]; //0~9 :

	Stage* stage_;						//�X�e�[�W���
	Princess* princess_;				//�P
	CharactorCreator* creator_;			//���f���E�L�����f�[�^�ǂݍ��݃N���X
	Collision* ray_;					//�����蔻��N���X
	Camera* camera_;					//�J�����N���X
	SpawnManager* spawnManager_;
	std::vector<JobManager*> player_;	//�v���C���[
	std::vector<CharactorManager*> charList_;	//�X�e�[�W��ɑ��݂���L�����N�^�[
	std::vector<CharactorManager*> killList_;	//���S�G�l�~�[���X�g

	enum scene
	{
		StartS = 0,
		MainS,
		EndS,
		NextS,
	};
	scene scene_;

	enum colored
	{
		isColor=0,
		noneColor,
	};

	bool failedFlg_;
	bool retryFlg_;
	bool nextSceneFlg_;
	bool failedChoiceFlg_;
	bool princessVoiceFlg_;
	bool startCameraMovefirstFlg_;
	bool startCameraMoveSecFlg_;
	int spawnAmount_;					//�X�|�[���Q�[�g�̐�
	int enemyCount_;
	unsigned int time_;
	float handXPos_; 
	float inputX;
	float failedUIPosY_;
	float reUIPosY_;

	void GameStart();	//�Q�[���J�n��������
	void GameMain();	//�Q�[�����C��
	void GameEnd();		//�Q�[���I��
	void NextScene();
	void GameOverChoice();

	void CollisionControl();			//�Փ˔���Ǘ�
	void EnemyDestroy();	//�G�l�~�[���S����
	JobManager* SetCharaJob(char* name, CharaType type);

	//�f�o�b�N
	D3D11_TEXT* debugText_;
	double insTime_, pushTime_;
	bool spawnFlg_;
	void PlayerDebug();
	//void EnemyDebug();
public:
	Main_Scene();
	virtual ~Main_Scene();

	void Init(/*HWND m_hWnd,ID3D11Device* m_pDevice,ID3D11DeviceContext* m_pDeviceContext*/);	//������
	void Destroy();
	//HRESULT DebugInit(ID3D11DeviceContext* m_pDeviceContext);								//�f�o�b�O�`�揉����
	//HRESULT EffectInit(ID3D11DeviceContext* m_pDeviceContext);
	/*void Render(D3DXMATRIX mView, D3DXMATRIX mProj);*/										//�`��
	void Update();
	void Render();
	//void EffectRender();	//�`��

	SceneBase* Update(SceneRoot* root);


	//�f�o�b�O�p
	DWORD start1, start2, end1, end2, result1, result2;
};