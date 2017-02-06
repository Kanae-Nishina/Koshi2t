//
//	@file	Spawn.h
//	@brief	�X�|�[���Q�[�g�N���X
//	@date	2016/11/25
//	@author	�m�ȍ��c
#pragma once
#include <time.h>
#include "./../Origin.h"
#include "./../Charactor/Enemy/EnemyJobManager.h"
#include "./../Read/SpawnGateRead.h"



class Spawn
{
private:
	int timeCount_;		//���ԃJ�E���g
	float scale_;		//�T�C�Y
	D3DXVECTOR3 rot_;	//��]

	SpawnGateAttr* spawn_;							//�X�|�[�����
	CharactorCreator* creator_;						//���f���ǂݍ���
	CharactorManager* tempCharactor_;				//���������G�l�~�[���ꎞ�ۑ��p
	CD3DXSKINMESH* enemyMesh_;						//���������G�l�~�[���b�V��
	std::vector<EnemyJobManager*> insEnemyList_;	//��x�ɐ������ꂽ�G�l�~�[���X�g

public:
	Spawn();
	~Spawn();
	void SpawnInit(SpawnGateAttr* spawnInfo, CD3DXSKINMESH* mesh);	//������
	void ListSet(CharactorManager* target);							//�X�|�[�����X�g�Z�b�g
	void ListReset();												//�X�|�[�����Z�b�g
	std::vector<EnemyJobManager*> EnemySpawn();						//�G�l�~�[�̐���
	D3DXVECTOR3 GetPos()const { return spawn_->pos_; };				//�X�|�[���Q�[�g�̍��W�擾
	D3DXVECTOR3 GetRot()const { return rot_; };						//�X�|�[���Q�[�g�̉�]�擾
	float GetScale()const { return scale_; };						//�X�|�[���Q�[�g�̃X�P�[���擾
	SpawnGateAttr* GetSpawnGateAttr()const { return spawn_; };		//�X�|�[���Q�[�g�̏��擾
};