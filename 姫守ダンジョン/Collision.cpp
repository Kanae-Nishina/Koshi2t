//
//	@file	Collision.cpp
//	@brief	�����蔻��Ǘ��N���X
//	@date	2016/11/14
//	@author�@�g�z��R

#include "Collision.h"

int* Collision::stageSpace_;
int Collision::spaceAmount_;


Collision::Collision()
{
	float fDistance = 0;
}


Collision::~Collision()
{
}

//
//	@brief	�X�e�[�W�z��̐ݒ�
void Collision::StageSlideInit()
{
	//�X�e�[�W�X�P�[��
	D3DXVECTOR3 stScale = STAGE_SCALE;
	int no = ((int)stScale.z / 2)*STAGE_SLIDE + (int)stScale.x / 2;

	stageSpace_ = new int[no];
	spaceAmount_ = no;
	for (int i = 0; i < no; i++)
	{
		stageSpace_[i] = Not;
	}
}

//
//	@brief			��Ԕԍ��擾
//	@param(pos)		���g�̍��W
//	@param(slide)	�ő啪�����ɏ��Z���鐔�B�������傫���قǕ����������Ȃ��Ȃ�
//	@note			1�X�e�[�W�������m�F�p�ɗp�ӁB
int Collision::SetSpaceNo(D3DXVECTOR3 pos, int slide)
{
	//x��������
	int sx = STAGE_SLIDE / slide;

	//�X�e�[�W�X�P�[��
	D3DXVECTOR3 stScale = STAGE_SCALE;

	//�␳�l(�X�e�[�W�X�P�[���̔���)
	D3DXVECTOR3 correction = { stScale.x / 2,0,stScale.z / 2 };

	////�X�e�[�W���W
	//D3DXVECTOR3 stagePos = { 0,0,0 };
	////�X�e�[�W���W�̕␳
	//D3DXVECTOR3 tempStagePos = { stagePos.x + correction.x,0,stagePos.z + correction.z };

	//���g�̍��W�␳
	D3DXVECTOR3 tempOwnPos = { pos.x + correction.x,0,pos.z + correction.z };
	//���g�̕␳���ꂽ���W����A���̃X�e�[�W�ɂ������Ԕԍ����Z�o
	int no = ((int)tempOwnPos.z / slide)*sx + (int)tempOwnPos.x / slide;

	return no;
}

//
//	@brief		��Ԕԍ��擾�A�X�e�[�W�z��ɃZ�b�g
//	@param(pos)	���g�̍��W
//	@return		�z��ɉ������Ȃ���΃Z�b�g�B����������-1��Ԃ�
void Collision::SetSpaceNoArray(D3DXVECTOR3 pos)
{
	//x��������
	int sx = STAGE_SLIDE;

	//�X�e�[�W�X�P�[��
	D3DXVECTOR3 stScale = STAGE_SCALE;

	//�␳�l(�X�e�[�W�X�P�[���̔���)
	D3DXVECTOR3 correction = { stScale.x / 2,0,stScale.z / 2 };

	//���g�̍��W�␳
	D3DXVECTOR3 tempOwnPos = { pos.x + correction.x,0,pos.z + correction.z };
	//���g�̕␳���ꂽ���W����A���̃X�e�[�W�ɂ������Ԕԍ����Z�o
	int no = ((int)tempOwnPos.z / 2)*sx + (int)tempOwnPos.x / 2;

	stageSpace_[no] = Existence;
}

//
//	@brief	�X�e�[�W�z��̍X�V
void Collision::StageSpaceReset()
{
	for (int i = 0; i < spaceAmount_; i++)
	{
		stageSpace_[i] = Not;
	}
}

//
//	@brief		�X�e�[�W�z��̗v�f��Ԃ̎擾
//	@param(no)	��Ԕԍ�
//	@note		�ő��ԕ������ŕ����������̋�Ԕԍ�
int Collision::GetStageSpace(int no)
{
	return stageSpace_[no];
}

//
//	@brief			���ӂ̃L�����N�^�[�Ƃ̋�Ԕԍ��̊m�F
//	@param(ownNo)	���g�̋�Ԕԍ�
//	@param(oppNo)	����̋�Ԕԍ�
//	@param(no)		�T������}�X�͈̔�(��������̔��a)
//	@param(slide)	�ő啪�����ɏ��Z���鐔�B�������傫���قǕ����������Ȃ��Ȃ�
bool Collision::CheckSpaceNo(int ownNo, int oppNo,int no,int slide)
{
	//x���̋�ԕ�����
	int sx = STAGE_SLIDE/slide;

	//����̋�Ԕԍ��������Ǝ����̎��ӂ̋�Ԕԍ��ƈ�v���邩�ǂ���
	for (int i = -no; i <= no; i++)
	{
		int mz = ownNo - sx*i - no;
		int pz = ownNo - sx*i + no;
		if (mz <= oppNo && oppNo <=pz)
		{
			return true;
		}
	}

	/*if ((ownNo - 1 <= oppNo && oppNo <= ownNo + 1)
		|| (ownNo - sx - 1 <= oppNo && oppNo <= ownNo - sx + 1)
		|| (ownNo + sx - 1 <= oppNo && oppNo <= ownNo + sx + 1))
	{
		return true;
	}*/

	return false;
}

//
//	@brief				�����ɂ��Փ˔���
//	@param(posA)		���g�̍��W
//	@param(posB)		����̍��W
//	@param(distance)	���苗��
bool Collision::CharaNear(D3DXVECTOR3 posA, D3DXVECTOR3 posB, float distance)
{
	float x = pow(posA.x - posB.x, 2);
	float z = pow(posA.z - posB.z, 2);
	float d1 = x + z;
	float d2 = pow(distance, 2);
	if (d1 <= d2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//
//	@breif			��������
//	@param (posA)	���g�̍��W
//	@param (posB)	����̍��W
//	@return			�����̓��
float Collision::Distance2(D3DXVECTOR3 posA, D3DXVECTOR3 posB)
{
	return pow(posA.x - posB.x, 2) + pow(posA.z - posB.z, 2);
}

bool Collision::RayIntersect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, CD3DXMESH* pMeshB, float* pfDistance, D3DXVECTOR3* pvNormal)
{
	BOOL boHit = false;
	D3DXMATRIX Inv;
	D3DXVECTOR3 vStart/*, vEnd*/, vDirection;
	//���C���o�����b�V���̈ʒu�E��]�����C�ɓK�p
	vStart = pos;
	vDirection = dir;
	//���C�𓖂Ă郁�b�V���������Ă������]���Ă���ꍇ�ł��Ώۂ̃��[���h�s��̋t�s���p����ΐ��������C��������
	D3DXMatrixInverse(&Inv, NULL, &pMeshB->m_World);
	D3DXVec3TransformCoord(&vStart, &vStart, &Inv);

	D3DXVec3Normalize(&vDirection, &vDirection);
	DWORD dwIndex = 0;
	D3DXIntersect(pMeshB->m_pMesh, &vStart, &vDirection, &boHit, &dwIndex, NULL, NULL, pfDistance, NULL, NULL);
	if (boHit)
	{
		//�������Ă���|���S���̒��_��������
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(pMeshB->m_pMesh, dwIndex, vVertex);
		D3DXPLANE p;
		//���̒��_���畽�ʕ������𓾂�
		D3DXPlaneFromPoints(&p, &vVertex[0], &vVertex[1], &vVertex[2]);
		//���ʕ������̌W�����@���̐���
		pvNormal->x = p.a;
		pvNormal->y = p.b;
		pvNormal->z = p.c;
		return true;
	}
	return false;
}

D3DXVECTOR3* Collision::SlideVector(D3DXVECTOR3 * out, const D3DXVECTOR3 & front, const D3DXVECTOR3 & normal)
{
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	return D3DXVec3Normalize(out, &(front - D3DXVec3Dot(&front, &normal_n) * normal_n));
}

D3DXVECTOR3 Collision::Slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //����x�N�g���i��������j

	//����x�N�g�� S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (pow(D3DXVec3Length(&N), 2)))*N;
	S.y = 0;

	return S;
}
//
//
//���̃|���S���̒��_��������
HRESULT Collision::FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices)
{
	DWORD i, k;
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	DWORD dwVertexNum = pMesh->GetNumVertices();
	DWORD dwPolyNum = pMesh->GetNumFaces();
	DWORD* pwPoly = NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);

	BYTE *pbVertices = NULL;
	FLOAT* pfVetices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMesh->GetVertexBuffer(&VB);
	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pvVertices[0].x = pfVetices[0];
		pvVertices[0].y = pfVetices[1];
		pvVertices[0].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pvVertices[1].x = pfVetices[0];
		pvVertices[1].y = pfVetices[1];
		pvVertices[1].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pvVertices[2].x = pfVetices[0];
		pvVertices[2].y = pfVetices[1];
		pvVertices[2].z = pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
	}
	return S_OK;
}


