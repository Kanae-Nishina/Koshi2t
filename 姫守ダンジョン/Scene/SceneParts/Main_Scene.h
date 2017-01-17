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

class Main_Scene :public Scene
{
private:
	bool failedFlg_;
	bool startCameraMovefirstFlg_;
	bool startCameraMoveSecFlg_;

	TD_Graphics* uiStart_;
	TD_Graphics* uiClear_;
	TD_Graphics* uiFailed_;
	TD_Graphics* uiTime_[UI_TIME]; //0~9 ; ,
	TD_Graphics* uiDebug_;
	
	enum scene
	{
		StartS=0,
		MainS,
		EndS,
		NextS,
	};
	scene scene_;

	Stage* stage_;						//�X�e�[�W���
	std::vector<JobManager*> player_;	//�v���C���[
	Princess* princess_;				//�P
	CharactorCreator* creator_;			//���f���E�L�����f�[�^�ǂݍ��݃N���X
	Collision* ray_;					//�����蔻��N���X
	Camera* camera_;					//�J�����N���X


	int spawnAmount_;					//�X�|�[���Q�[�g�̐�
	SpawnManager* spawnManager_;

	void CollisionControl();			//�Փ˔���Ǘ�

	std::vector<CharactorManager*> charList_;	//�X�e�[�W��ɑ��݂���L�����N�^�[
	std::vector<EnemyJobManager*> enemyList_;	//�X�e�[�W��ɑ��݂���G�l�~�[
	std::vector<EnemyJobManager*> killList_;	//���S�G�l�~�[���X�g
	unsigned int time_;

	void GameStart();	//�Q�[���J�n��������
	void GameMain();	//�Q�[�����C��
	void GameEnd();		//�Q�[���I��

	void EnemyDestroy();	//�G�l�~�[���S����
	JobManager* SetCharaJob(char* name, CharaType type);

							//�G�t�F�N�g	
	//D3D11_SPRITE* uisword_;
	//D3D11_SPRITE* uiseeld_;
	//D3D11_SPRITE* uimagic_;
	//D3D11_SPRITE* uibom_;
	//D3D11_SPRITE* uititle_;


	//�f�o�b�N
	D3D11_TEXT* debugText_;
	double insTime_,pushTime_;
	bool spawnFlg_;

	void PlayerDebug();
	//void EnemyDebug();

	//map<string, TD_Graphics*> Title_UI;

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

};