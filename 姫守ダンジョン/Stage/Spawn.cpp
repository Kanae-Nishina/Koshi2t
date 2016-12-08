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
}

//
//	@brief	�f�X�g���N�^
Spawn::~Spawn()
{

}

////
////	@brief	�X�|�[���̏�����
//void Spawn::SpawnInit(const char* name)
//{
//
//	char FileName[80];
//	memset(FileName, 0, sizeof(FileName));
//	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Stage/");
//	strcat_s(FileName, sizeof(FileName), name);
//	if (LoadXMesh(FileName))
//	{
//		return;
//	}
//
//	m_vPos = { 0,0,5 };
//	spawnID_ = 0;
//	amount_ = 5;
//
//
//}

//
//	@brief	�X�|�[���Q�[�g�̏�����
void Spawn::SpawnInit(SpawnGateAttr* spawnInfo)
{
	scale_ = 0.5;
	rot_ = D3DXVECTOR3(0,0,0);
	spawn_ = spawnInfo;
	//memset(spawn_, 0, sizeof(spawn_));
	//memcpy(spawn_, spawnInfo, sizeof(spawn_));
	//spawnID_ = spawnInfo->id_;
	//memset(enemyName_, 0, sizeof(enemyName_));
	//strcpy_s(enemyName_, sizeof(enemyName_), spawnInfo->enemyName_);
	//amount_ = spawnInfo->amount_;
}

//
//	@brief	�G�l�~�[���X�g�̃Z�b�g
void Spawn::ListSet(ParameterRead* param, CharactorManager* target)
{
	srand((unsigned)time(NULL));
	tempParameter_ = param;
	tempCharactor_ = target;
	int spawnTime = FPS*spawn_->interval_;
	
	if (++timeCount_%spawnTime == 0)
	{
		if (strcmp(spawn_->enemyName_, "�X���C��") == 0)
		{
			SlimeSet();
		}
		else if (strcmp(spawn_->enemyName_, "�S�u����") == 0)
		{
			GoblinSet();
		}
		else if (strcmp(spawn_->enemyName_, "�X�P���g��") == 0)
		{
			SkeletonSet();
		}
	}
}

//
//	@brief	�X���C���Z�b�g
void Spawn::SlimeSet()
{
	int range = spawn_->spawnRange_;
	int amount_ = spawn_->amount_;
	D3DXVECTOR3 pos = spawn_->pos_;
	for (int i = 0; i < amount_; i++)
	{
		EnemyJobManager* enemy = new Slim;
		enemy->SetParameter(tempParameter_->GetEnemyParamList(spawn_->enemyName_));
		enemy->SetTarget(tempCharactor_);
		enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
		enemy->m_Pos = D3DXVECTOR3(rand() % range + (pos.x - range / 2), 0, rand() % range + (pos.z - range / 2));
		insEnemyList_.push_back(enemy);
		//SAFE_DELETE(enemy);
	}
}

//
//	@brief	�S�u�����Z�b�g
void Spawn::GoblinSet()
{
	int range = spawn_->spawnRange_;
	int amount_ = spawn_->amount_;
	D3DXVECTOR3 pos = spawn_->pos_;
	for (int i = 0; i < amount_; i++)
	{
		EnemyJobManager* enemy = new Goblin;
		enemy->SetParameter(tempParameter_->GetEnemyParamList(spawn_->enemyName_));
		enemy->SetTarget(tempCharactor_);
		enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
		enemy->m_Pos = D3DXVECTOR3(rand() % range + (pos.x - range / 2), 0, rand() % range + (pos.z - range / 2));
		insEnemyList_.push_back(enemy);
		//SAFE_DELETE(enemy);
	}
}

//
//	@brief	�X�P���g���Z�b�g
void Spawn::SkeletonSet()
{
	int range = spawn_->spawnRange_;
	int amount_ = spawn_->amount_;
	D3DXVECTOR3 pos = spawn_->pos_;
	for (int i = 0; i < amount_; i++)
	{
		EnemyJobManager* enemy = new Skeleton;
		enemy->SetParameter(tempParameter_->GetEnemyParamList(spawn_->enemyName_));
		enemy->SetTarget(tempCharactor_);
		enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
		enemy->m_Pos = D3DXVECTOR3(rand() % range + (pos.x - range / 2), 0, rand() % range + (pos.z - range / 2));
		insEnemyList_.push_back(enemy);
		//SAFE_DELETE(enemy);
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

////
////	@brief	�`��
//void Spawn::SpawnRender()
//{
//	Render(m_vPos,D3DXVECTOR3(0,0,0),0.2);
//}