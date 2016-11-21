//
//	@file	Stage.h
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@outher	�m�ȍ��c

#pragma once
#include "./../Mesh/CD3DXMESH.h"

using namespace STATICMESH;
class Stage
{
	CD3DXMESH* stageMesh_;
public:
	Stage();
	~Stage();

	void Read(HWND m_phWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext,const char* fileName);		//������
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);		//�`��

	CD3DXMESH* GetMeshInfo()const { return stageMesh_; };		//���b�V���̎擾
};