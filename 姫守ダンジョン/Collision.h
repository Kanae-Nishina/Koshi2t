//
//	@file	Collision.h
//	@brief	�����蔻��Ǘ��N���X
//	@date	2016/11/14
//	@author �g�z��R
//	@note	��ԕ����ɂ��Փ˔���ǉ�(�m�ȍ��c)

#pragma once
#include "Origin.h"
#include "./Mesh/CD3DXSKINMESH.h"
#include "./Mesh/CD3DXMESH.h"

#define RAY_DISTANCE 3			//���C�������
#define STAGE_SLIDE 64			//�X�e�[�WX���̃}�X�̐�
#define STAGE_SCALE { 68,0,36}	//�X�e�[�W�̃X�P�[��

class Collision
{
public:
	~Collision();
	Collision();

	//��Ԕԍ��̎擾
	int SetSpaceNo(D3DXVECTOR3 pos,int slide);	
	//��Ԕԍ��ɂ��Փ˔���
	bool CheckSpaceNo(int ownNo, int oppNo, int no, int slide);	
	//�����ɂ��Փ˔���
	bool CharaNear(D3DXVECTOR3 posA, D3DXVECTOR3 posB, float distance);	
	//���C�ɂ��Փ˔���
	bool RayIntersect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, CD3DXMESH* Mesh_b, float* pfDistance, D3DXVECTOR3* pvNormal);	
	//����x�N�g���擾
	D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);	
	//���C�̏Փ˒n�_�̃|���S�����_�̔���
	HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices); 
};

