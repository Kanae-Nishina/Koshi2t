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

class SpawnManager
{
private:
	TD_Graphics* seal_UI;
	CharactorCreator* creator_;
	CD3DXMESH* spawnMesh_;
	SpawnGateRead* spawnGateRead_;
	SpawnGate* spawnGate_;

	int timeCount_;
	bool uiDrawFlg_;

	//char stageTye[30];					//���݂̃X�e�[�W�^�C�v
	std::vector<Spawn*> spawnList_;			//���ݑ��݂��Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn*> functionList_;		//�@�\���Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn*> renderList_;		//�`�悷��X�|�[���Q�[�g���X�g���X�g
	Spawn* sealSpawn_;						//���󂳂��X�|�[���Q�[�g
	
	void SpawnSet();	//�X�|�[���Q�[�g�̏���

public:
	SpawnManager();
	~SpawnManager();

	void Init(char* name);
	void Reset();
	void Update(/*ParameterRead* param, */CharactorManager* target);
	void SealSpawn(Spawn* spawn);
	void Render();
	std::vector<EnemyJobManager*> OutEnemy();
	std::vector<Spawn*> GetSpawnList() { return spawnList_; };

};