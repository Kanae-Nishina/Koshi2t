//
//	@file	Stage.cpp
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@outher	�m�ȍ��c
#include "./Stage.h"

//
//	@brief	�R���X�g���N�^
Stage::Stage()
{
	stageMesh_ = new CD3DXMESH;
	m_Pos = D3DXVECTOR3(0, 0, 0);
}

//
//	@brief �f�X�g���N�^
Stage::~Stage()
{
	SAFE_DELETE(stageMesh_);
}

//
//	@brief						X�t�@�C���ǂݍ���
void Stage::Read(const char* StageName)
{
	char FileNameF[80];
	memset(FileNameF, 0, sizeof(FileNameF));
	strcpy_s(FileNameF, sizeof(FileNameF), "./Model/XFiles/Stage/");
	strcat_s(FileNameF, sizeof(FileNameF), StageName);

	if (FAILED(stageMesh_->LoadXMesh(FileNameF)))
	{
		return;
	}
	
}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Stage::Render()
{
	stageMesh_->Render(m_Pos,0,1);
}