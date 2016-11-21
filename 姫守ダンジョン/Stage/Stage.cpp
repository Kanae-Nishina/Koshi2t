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
	stageMeshFloor_ = new CD3DXMESH;
	stageMeshWall_ = new CD3DXMESH;
}

//
//	@brief �f�X�g���N�^
Stage::~Stage()
{
	SAFE_DELETE(stageMeshFloor_);
	SAFE_DELETE(stageMeshWall_);
}

//
//	@brief						X�t�@�C���ǂݍ���
//	@param (m_hWnd)				�E�B���h�E�n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
//	@param (FloorName)			����X�t�@�C����
//	@param (WallName)			�ǂ�X�t�@�C����
void Stage::Read(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* FloorName, const char* WallName)
{
	char FileNameF[80];
	memset(FileNameF, 0, sizeof(FileNameF));
	strcpy_s(FileNameF, sizeof(FileNameF), "./Model/XFiles/Stage/");
	strcat_s(FileNameF, sizeof(FileNameF), FloorName);
	if (FAILED(stageMeshFloor_->Init(m_hWnd, m_pDevice, m_pDeviceContext, FileNameF)))
	{
		return;
	}
	
	char FileNameW[80];
	memset(FileNameW, 0, sizeof(FileNameW));
	strcpy_s(FileNameW, sizeof(FileNameW), "./Model/XFiles/Stage/");
	strcat_s(FileNameW, sizeof(FileNameW), WallName);
	if (FAILED(stageMeshWall_->Init(m_hWnd, m_pDevice, m_pDeviceContext, FileNameW)))
	{
		return;
	}
}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Stage::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	stageMeshFloor_->Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
	stageMeshWall_->Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
}