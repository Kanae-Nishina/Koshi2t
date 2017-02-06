//
//	@file	Spawn.cpp
//	@brief	�X�|�[���Q�[�g�N���X
//	@date	2016/11/25
//	@author	�m�ȍ��c

#include "./Spawn.h"

//
//	@brief	�R���X�g���N�^
Spawn::Spawn()
	:timeCount_(0)
{
	enemyMesh_ = new CD3DXSKINMESH;
	creator_ = new CharactorCreator;
}

//
//	@brief	�f�X�g���N�^
Spawn::~Spawn()
{
	delete creator_;
	creator_ = nullptr;
}

//
//	@brief				�X�|�[���Q�[�g�̏�����
//	@param(spawnInfo)	�X�|�[���Q�[�g�̏��
//	@param(mesh)		�X�|�[���Q�[�g�̃��b�V��
void Spawn::SpawnInit(SpawnGateAttr* spawnInfo, CD3DXSKINMESH* mesh)
{
	scale_ = 0.5;
	rot_ = D3DXVECTOR3(0, 0, 0);
	spawn_ = spawnInfo;
	enemyMesh_ = creator_->LoadChara(spawn_->enemyName_);
}

//
//	@brief			�G�l�~�[���X�g�̃Z�b�g
//	@param(target)	�^�[�Q�b�g�L����
void Spawn::ListSet(CharactorManager* target)
{
	srand((unsigned)time(NULL));
	tempCharactor_ = target;
	int spawnTime = FPS*spawn_->interval_;

	if (timeCount_++%spawnTime == 0)
	{
		int width = spawn_->leftBack_.x +spawn_->rightFront_.x;		//��
		int height = spawn_->leftBack_.z +spawn_->rightFront_.z;	//����(z��)
		D3DXVECTOR3 tempPos = D3DXVECTOR3(spawn_->pos_.x - spawn_->leftBack_.x, 0, spawn_->pos_.z +spawn_->leftBack_.z);	//�o�����W�̈�ԍ���
		int amount_ = spawn_->amount_;
		for (int i = 0; i < amount_; i++)
		{
			EnemyJobManager* enemy;
			if (strcmp(spawn_->enemyName_, "�X���C��") == 0)
			{
				enemy = new Slim;
			}
			else if (strcmp(spawn_->enemyName_, "�S�u����") == 0)
			{
				enemy = new Goblin;
			}
			else if (strcmp(spawn_->enemyName_, "�X�P���g��") == 0)
			{
				enemy = new Skeleton;
			}
			enemy->CharaInit(spawn_->enemyName_);
			enemy->SetModel(enemyMesh_);
			enemy->SetTarget(tempCharactor_);
			enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
			enemy->m_Pos = D3DXVECTOR3(rand() % width +tempPos.x, 0, tempPos.z - rand() % height);
			insEnemyList_.push_back(enemy);
		}
	}
}

//
//	@brief	�G�l�~�[�̃X�|�[��
std::vector<EnemyJobManager*> Spawn::EnemySpawn()
{
	return insEnemyList_;
}

//
//	@brief	�G�l�~�[���X�g�̃��Z�b�g
void Spawn::ListReset()
{
	insEnemyList_.clear();
}