//
//	@file	Stage.cpp
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@author	�m�ȍ��c
#include "./Stage.h"

//
//	@brief	�R���X�g���N�^
Stage::Stage()
{
	stageMesh_ = new CD3DXMESH;
	m_Pos = D3DXVECTOR3(0, -0.2, 0);
	skyMesh_ = new CD3DXMESH;
	gate_ = new CD3DXMESH;
	abyssGround_ = new CD3DXMESH;


}

//
//	@brief �f�X�g���N�^
Stage::~Stage()
{
	SAFE_DELETE(stageMesh_);
	SAFE_DELETE(skyMesh_);
	SAFE_DELETE(gate_);
	SAFE_DELETE(abyssGround_);
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

	if (FAILED(skyMesh_->LoadXMesh("./Model/XFiles/Stage/sky.x")))
	{
		return;
	}
	
	if (FAILED(gate_->LoadXMesh("./Model/XFiles/Stage/gate.x")))
	{
		return;
	}

	if (FAILED(abyssGround_->LoadXMesh("./Model/XFiles/Stage/mapbase.x")))
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
	//static float scale = 1;
	//�f�o�b�N�p
	//scale += -((GetKeyState(VK_F1) & 0x80)*0.0001) + ((GetKeyState(VK_F2) & 0x80)*0.0001);
	//
	stageMesh_->Render(m_Pos,D3DXVECTOR3(0,0,0),1);

	skyMesh_->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(D3DXToRadian(90), 0, 0), 3);

	gate_->Render(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1);

	abyssGround_->Render(D3DXVECTOR3(0, -2, 0), D3DXVECTOR3(0, 0, 0), 1);
}