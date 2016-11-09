//
//	@file	Camera.cpp
//	@brief	�J�����֘A
//	@date	2016/11/08
//	@outher	�m�ȍ��c

#include "Camera.h"

//
//	@brief	�R���X�g���N�^
Camera::Camera()
{
	movePow_ = D3DXVECTOR3(0, 48, -40);
	gazePoint_ = D3DXVECTOR3(0,0,0);
}

//
//	@brief	�f�X�g���N�^
Camera::~Camera()
{
}

//
//	@brief	�X�V����
//	@param (pos)	
//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Camera::Render()
{
	// �R�l�̎��_�����@�r���[�g�����X�t�H�[�� �J�������L�����̌��ɔz�u���邾��
	static D3DXVECTOR3 camPos=movePow_;
	static D3DXVECTOR3 lookPos=gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu

	//���_�ƒ����_�̗������L�����̎p���i��]�ƈʒu�j�s��ŋȂ��Ĉړ�����΂���
	
	D3DXMATRIX OriMat, Tran, Yaw;
	D3DXMatrixTranslation(&Tran, 0, 0, 0);
	D3DXMatrixRotationY(&Yaw, 0);
	OriMat = Yaw*Tran;

	D3DXVec3TransformCoord(&camPos, &camPos, &OriMat);
	D3DXVec3TransformCoord(&lookPos, &lookPos, &OriMat);

	D3DXMatrixLookAtLH(&mView_, &camPos, &lookPos, &vUpVec);

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMatrixPerspectiveFovLH(&mProj_, D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}