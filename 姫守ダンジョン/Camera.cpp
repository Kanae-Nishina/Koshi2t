//
//	@file	Camera.cpp
//	@brief	�J�����֘A
//	@date	2016/11/08
//	@outher	�m�ȍ��c
//	@note	������(2016/11/08)

#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Camera::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	// �R�l�̎��_�����@�r���[�g�����X�t�H�[�� �J�������L�����̌��ɔz�u���邾��
	D3DXVECTOR3 vEyePt(0.0f, 2.0f, -4.0f); //�J�����i���_�j�ʒu
	D3DXVECTOR3 vLookatPt(0.0f, 1.7f, 0.0f);//�����ʒu
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu

	//���_�ƒ����_�̗������L�����̎p���i��]�ƈʒu�j�s��ŋȂ��Ĉړ�����΂���
	D3DXMATRIX OriMat, Tran, Yaw;
	D3DXMatrixTranslation(&Tran, 0, 0, 0);
	D3DXMatrixRotationY(&Yaw, 0);
	OriMat = Yaw*Tran;

	D3DXVec3TransformCoord(&vEyePt, &vEyePt, &OriMat);
	D3DXVec3TransformCoord(&vLookatPt, &vLookatPt, &OriMat);

	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}