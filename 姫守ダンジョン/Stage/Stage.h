//
//	@file	Stage.h
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@outher	�m�ȍ��c

#pragma once
#include "./../Mesh/CD3DXMESH_ANIM.h"

class Stage
{
	CD3DXMESH_ANIM* stageMesh_;
public:
	Stage();
	~Stage();

	void Read(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext,const char* fileName);		//������
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);		//�`��

	CD3DXMESH_ANIM* GetMeshInfo()const { return stageMesh_; };		//���b�V���̎擾
};