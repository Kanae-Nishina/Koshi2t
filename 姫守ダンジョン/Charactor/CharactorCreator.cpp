#include "./CharactorCreator.h"

std::vector<CharaModel*> CharactorCreator::charaModelList_;
std::vector<StageModel*> CharactorCreator::stageModelList_;
char CharactorCreator::player1_[10];
char CharactorCreator::player2_[10];
char CharactorCreator::player3_[10];
char CharactorCreator::player4_[10];

//
//	@brief	���f���̃��[�h
void CharactorCreator::LoadModel()
{
	//X�t�@�C���̏��ǂݍ���
	XFileRead* xfileRead = new XFileRead;
	xfileRead->ReadXFilePath();

	//�L�������f�����[�h
	std::vector<XFile*> chara = xfileRead->GetModelFile();
	for (auto c : chara)
	{
		CharaModel* charaM = new CharaModel;
		strcpy(charaM->name_, c->GetCharName());
		//memcpy(charaM->name_, c->GetCharName(), sizeof(c->GetCharName()+1));
		charaM->mesh_ = new CD3DXSKINMESH;
		charaM->mesh_->CreateFromX(c->GetFilePath());
		charaModelList_.push_back(charaM);
	}

	//�X�e�[�W���f�����[�h
	std::vector<XFile*> stage = xfileRead->GetStageFile();
	for (auto s : stage)
	{
		StageModel* stageM = new StageModel; 
		strcpy(stageM->name_, s->GetCharName());
		stageM->mesh_ = new CD3DXMESH;
		stageM->mesh_->LoadXMesh(s->GetFilePath());
		stageModelList_.push_back(stageM);
	}

	//�X�|�[�����f�����[�h
	XFile* file = xfileRead->GetXFile("�X�|�[��");
	StageModel* spawnM = new StageModel;
	strcpy(spawnM->name_, file->GetCharName());
	spawnM->mesh_ = new CD3DXMESH;
	spawnM->mesh_->LoadXMesh(file->GetFilePath());
	stageModelList_.push_back(spawnM);

	//���[�V�����f�[�^�̃��[�h
	MotionRead::PlayerMotionRead();
	MotionRead::EnemyMotionRead();

	//�p�����[�^�[�f�[�^�̃��[�h
	ParameterRead::SetJobParameter();
	ParameterRead::SetPricessParameter();
	ParameterRead::SetEnemyParameter();
}

//
//	@brief	�X�e�[�W���f���̎擾
CD3DXMESH* CharactorCreator::GetStageModel(char* name)
{
	for (auto s : stageModelList_)
	{
		if (strcmp(name, s->name_) == 0)
		{
			return s->mesh_;
		}
	}

	return nullptr;
}

//
//	@brief	�L�������f���̎擾
CD3DXSKINMESH* CharactorCreator::GetCharaModel(char* name)
{
	for (auto c : charaModelList_)
	{
		if (strcmp(name, c->name_) == 0)
		{
			return c->mesh_;
		}
	}

	return nullptr;
}

//
//	@brief	���
void CharactorCreator::Destroy()
{
	for (auto s : stageModelList_)
	{
		SAFE_DELETE(s->mesh_);
	}
	stageModelList_.clear();

	for (auto c : charaModelList_)
	{
		SAFE_DELETE(c->mesh_);
	}
	charaModelList_.clear();
}