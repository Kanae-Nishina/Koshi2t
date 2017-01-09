//
//	@file	SpawnManager.cpp
//	@brief	�X�|�[���Q�[�g�Ǘ��N���X
//	@date	2016/11/28
//	@author	�m�ȍ��c

#include "./SpawnManager.h"

//
//	@brief	�R���X�g���N�^
SpawnManager::SpawnManager()
{
	spawnGateRead_ = new SpawnGateRead;
}

//
//	@brief	�f�X�g���N�^
SpawnManager::~SpawnManager()
{
	delete spawnGateRead_;
	spawnGateRead_ = nullptr;
	//delete spawnGate_;
	//spawnGate_ = nullptr;

	SAFE_DELETE(spawnMesh_);
	spawnList_.clear();
}

//
//	@brief	������
void SpawnManager::Init(char* name)
{
	CharactorCreator* creator = new CharactorCreator;
	spawnMesh_ = creator->GetStageModel(name);
	//delete creator;
	//creator = nullptr;
	SpawnSet();
	/*spawnMesh_ = new CD3DXMESH;

	char FileName[80];
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Stage/");
	strcat_s(FileName, sizeof(FileName), name);
	if (FAILED(spawnMesh_->LoadXMesh(FileName)))
	{
		return;
	}

	SpawnSet();*/
}

//
//	@brief	�X�|�[���Q�[�g�̏���
void SpawnManager::SpawnSet()
{
	spawnGateRead_->SpawnGate_Read();
	spawnGate_ = spawnGateRead_->GetSpawnGate("stage5");
	std::vector<SpawnGateAttr*> tempAttr = spawnGate_->GetStageAllSpawnGate();
	for (int i = 0; i < spawnGate_->GetCount(); i++)
	{
		Spawn* temp = new Spawn;
		temp->SpawnInit(tempAttr[i]);
		spawnList_.push_back(temp);
		//functionList_.push_back(temp);
		//renderList_.push_back(temp);
	}
}

//
//	@brief	���Z�b�g
void SpawnManager::Reset()
{
	timeCount_ = 0;
	spawnList_.clear();
	functionList_.clear();
	renderList_.clear();
	sealSpawn_ = nullptr;


	spawnGateRead_->SpawnGate_Read();
	spawnGate_ = spawnGateRead_->GetSpawnGate("stage5");
	std::vector<SpawnGateAttr*> tempAttr = spawnGate_->GetStageAllSpawnGate();
	for (int i = 0; i < spawnGate_->GetCount(); i++)
	{
		Spawn* temp = new Spawn;
		temp->SpawnInit(tempAttr[i]);
		spawnList_.push_back(temp);
		//functionList_.push_back(temp);
		//renderList_.push_back(temp);
	}
}

//
//	@brief	�X�V����
void SpawnManager::Update(/*ParameterRead* param, */CharactorManager* target)
{
	if (!spawnList_.empty())
	{
		for (auto s : spawnList_)
		{
			s->ListSet(target);
		}
	}
}

//
//	@brief	�G�l�~�[�̃X�|�[��
std::vector<EnemyJobManager*> SpawnManager::OutEnemy()
{
	std::vector<EnemyJobManager*> tempPush;
	if (!spawnList_.empty())
	{
		for (auto f : spawnList_)
		{
			if (!f->EnemySpawn().empty())
			{
				std::vector<EnemyJobManager*> temp = f->EnemySpawn();
				for (auto e : temp)
				{
					tempPush.push_back(e);
				}
				f->ListReset();
			}
		}
	}

	return tempPush;
}

//
//	@brief	�X�|�[���̕���
void SpawnManager::SealSpawn(Spawn* spawn)
{
	sealSpawn_ = spawn;

	if (sealSpawn_ != nullptr)
	{
		auto elS = std::find(spawnList_.begin(), spawnList_.end(), sealSpawn_);
		//auto elF = std::find(functionList_.begin(), functionList_.end(), sealSpawn_);
		//auto elR = std::find(renderList_.begin(), renderList_.end(), sealSpawn_);

		delete(*elS);
		spawnList_.erase(elS);
		//functionList_.erase(elF);
		//renderList_.erase(elR);
	}
}

//
//	@brief	�`��
void SpawnManager::Render()
{
	if (!spawnList_.empty())
	{
		for (auto s : spawnList_)
		{
			spawnMesh_->Render(s->GetPos(), s->GetRot(), s->GetScale());
		}
	}
}