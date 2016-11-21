//
//	@file	Stage.h
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@outher	�m�ȍ��c

#pragma once
#include "./../Mesh/CD3DXMESH_ANIM.h"

class Stage
{
	CD3DXMESH_ANIM* stageMeshFloor_;
	CD3DXMESH_ANIM* stageMeshWall_;
public:
	Stage();
	~Stage();

	void Read(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext,const char* FloorName, const char* WallName);		//������
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);		//�`��

	CD3DXMESH_ANIM* GetMeshFloorInfo()const { return stageMeshFloor_; };		//���b�V���̎擾
	CD3DXMESH_ANIM* GetMeshWallInfo()const { return stageMeshWall_; };		//���b�V���̎擾
};