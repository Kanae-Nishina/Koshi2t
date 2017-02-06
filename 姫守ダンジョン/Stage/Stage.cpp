//
//	@file	Stage.cpp
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@author	�m�ȍ��c
#include "./Stage.h"

CD3DXMESH* Stage::stage_;

//
//	@brief	�R���X�g���N�^
Stage::Stage()
{
	creator_ = new CharactorCreator;
}

//
//	@brief	�f�X�g���N�^
Stage::~Stage()
{
	SAFE_DELETE(stage_);
	delete creator_;
	creator_ = nullptr;
}

//
//	@brief				������
//	@param(stageName)	�X�e�[�W��
void Stage::Init(char* stageName)
{
	stage_ = creator_->LoadStage(stageName);
}

//
//	@brief	���݂���X�e�[�W�̃��b�V�����擾
CD3DXMESH* Stage::GetMeshInfo()
{
	return stage_;
}

//
//	@brief			�`��
void Stage::Render()
{
	stage_->Render(D3DXVECTOR3(0, -0.01, 0), D3DXVECTOR3(0, 0, 0), 1);
}