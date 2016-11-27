//
//	@file	Spawn.h
//	@brief	�X�|�[���Q�[�g�N���X
//	@date	2016/11/24
//	@outher	�m�ȍ��c
#pragma once
#include <time.h>
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH.h"
#include "./../Charactor/Enemy/EnemyJobManager.h"



class Spawn :public CD3DXMESH
{
private:
	int spawnID_;		//�X�|�[���ԍ�
	int amount_;		//��x�ɐ�������G�l�~�[�̐�
	char enemyName_[30];	//��������G�l�~�[��
	std::vector<EnemyJobManager*> insEnemyList_;
public:
	Spawn();
	~Spawn();
	std::vector<EnemyJobManager*> EnemySpawn();
	void SpawnInit(const char* name);
	void ListSet(ParameterRead* param,CharactorManager* target);
	void ListReset();

	void SpawnRender();		//�`��
};