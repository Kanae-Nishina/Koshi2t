#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH.h"
#include "./../Read/SpawnGateRead.h"
#include "./Spawn.h"

class SpawnManager
{
private:
	CD3DXMESH* spawnMesh_;
	SpawnGateRead* spawnGateRead_;
	SpawnGate* spawnGate_;

	int timeCount_;

	//char stageTye[30];					//���݂̃X�e�[�W�^�C�v
	std::vector<Spawn*> spawnList_;			//���ݑ��݂��Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn*> functionList_;		//�@�\���Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn*> renderList_;		//�`�悷��X�|�[���Q�[�g���X�g���X�g
	Spawn* sealSpawn_;						//���󂳂��X�|�[���Q�[�g
	
	void SpawnSet();	//�X�|�[���Q�[�g�̏���

public:
	SpawnManager();
	~SpawnManager();

	void Init(const char* name);
	void Reset();
	void Update(ParameterRead* param, CharactorManager* target);
	void SealSpawn(Spawn* spawn);
	void Render();
	std::vector<EnemyJobManager*> OutEnemy();
	std::vector<Spawn*> GetSpawnList() { return spawnList_; };

};