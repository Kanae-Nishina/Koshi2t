//
//	@file	Stage.h
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@outher	�m�ȍ��c

#pragma once
#include "./../Mesh/CD3DXMESH.h"


class Stage
{
	CD3DXMESH* stageMesh_;
	CD3DXMESH* skyMesh_;
	CD3DXMESH* gate_;
	CD3DXMESH* abyssGround_;
	D3DXVECTOR3 m_Pos;
public:
	Stage();
	~Stage();

	void Read(const char* StageName);		//������
	void Render();		//�`��

	CD3DXMESH* GetMeshInfo()const { return stageMesh_; };		//���b�V���̎擾
};