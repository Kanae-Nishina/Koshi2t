//
//	@file	Spawn.h
//	@brief	�X�|�[���Q�[�g�N���X
//	@date	2016/11/25
//	@author	�m�ȍ��c
#pragma once
#include <time.h>
#include "./../Origin.h"
//#include "./../Mesh/CD3DXMESH.h"
#include "./../Charactor/Enemy/EnemyJobManager.h"
#include "./../Read/SpawnGateRead.h"



class Spawn/* :public CD3DXMESH*/
{
private:
	int timeCount_;
	float scale_;
	D3DXVECTOR3 rot_;

	SpawnGateAttr* spawn_;
	//ParameterRead* tempParameter_;
	CharactorManager* tempCharactor_;

	//int spawnID_;		//�X�|�[���ԍ�
	//int amount_;		//��x�ɐ�������G�l�~�[�̐�
	//char enemyName_[30];	//��������G�l�~�[��
	std::vector<EnemyJobManager*> insEnemyList_;

	void SlimeSet();
	void GoblinSet();
	void SkeletonSet();
public:
	Spawn();
	~Spawn();
	std::vector<EnemyJobManager*> EnemySpawn();
	//void SpawnInit(const char* name);
	void SpawnInit(SpawnGateAttr* spawnInfo);
	//void ListSet(ParameterRead* param,CharactorManager* target);
	void ListSet(CharactorManager* target);
	void ListReset();
	D3DXVECTOR3 GetPos()const { return spawn_->pos_; };
	D3DXVECTOR3 GetRot()const { return rot_; };
	float GetScale()const { return scale_; };
	SpawnGateAttr* GetSpawnGateAttr()const { return spawn_; };

	//void SpawnRender();		//�`��
};