//
//	@file	SpawnManager.h
//	@brief	�X�|�[���Q�[�g�Ǘ��N���X
//	@date	2016/11/28
//	@author	�m�ȍ��c

#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH.h"
#include "./../Read/SpawnGateRead.h"
#include "./Spawn.h"
#include "./../Charactor/CharactorCreator.h"
#include "./../UI/TD_Graphics.h"
#include "./../Camera.h"
#include "./../Effekseer/Effect.h"

class SpawnManager
{
private:
	TD_Graphics* seal_UI;						//���󎞂�UI
	CharactorCreator* creator_;					//���f���ǂݍ��ݗp�N���X
	CD3DXMESH* spawnMesh_;						//�X�|�[���Q�[�g�̃��b�V��
	SpawnGateRead* spawnGateRead_;				//�X�|�[���Q�[�g���ǂݍ��݃N���X
	SpawnGate* spawnGate_;						//�X�|�[���Q�[�g���
	Spawn* sealSpawn_;							//���󂳂��X�|�[���Q�[�g
	std::vector<Spawn*> spawnList_;				//���ݑ��݂��Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn*> functionList_;			//�@�\���Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn*> renderList_;			//�`�悷��X�|�[���Q�[�g���X�g���X�g
	std::vector<CD3DXSKINMESH*> enemyMesh_List;	//�`�悳���G�l�~�[���b�V�����X�g

	int timeCount_;		//���ԃJ�E���g
	bool uiDrawFlg_;	//���󎞂�UI�`��t���O

	void SpawnSet();	//�X�|�[���Q�[�g�̏���

public:
	SpawnManager();
	~SpawnManager();

	void Init(char* name);										//������
	void Reset();												//���Z�b�g
	void Update(CharactorManager* target);						//�X�V
	void SealSpawn(Spawn* spawn);								//����
	void Render();												//�`��
	CD3DXMESH* GetMesh()const { return spawnMesh_; };			//�X�|�[���Q�[�g�̃��b�V�����擾
	std::vector<EnemyJobManager*> OutEnemy();					//���������G�l�~�[
	std::vector<Spawn*> GetSpawnList() { return spawnList_; };	//�X�|�[���Q�[�g�̏�񃊃X�g

};