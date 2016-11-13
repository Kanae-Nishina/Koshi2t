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
	zoom = 4;

}

//
//	@brief	�f�X�g���N�^
Camera::~Camera()
{
}

//
//	@brief	�X�V
void Camera::Update()
{
	DebugMove();
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
	D3DXVECTOR3 camPos=movePow_;
	D3DXVECTOR3 lookPos=gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu

	D3DXMatrixTranslation(&tran_, 0, 0, 0);
	D3DXMatrixRotationY(&yaw_, 0);
	oriMat_ = yaw_*tran_;

	D3DXVec3TransformCoord(&camPos, &camPos, &oriMat_);
	D3DXVec3TransformCoord(&lookPos, &lookPos, &oriMat_);

	D3DXMatrixLookAtLH(&mView_, &camPos, &lookPos, &vUpVec);

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMatrixPerspectiveFovLH(&mProj_, D3DX_PI / zoom, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}

//
//	@brief	�f�o�b�O�p�J�����ړ�	
void Camera::DebugMove()
{
	static float Yaw = 0, Roll = -11;
	Yaw += -(GetKeyState(VK_LEFT) & 0x80)*0.00005 + (GetKeyState(VK_RIGHT) & 0x80)*0.00005;
	Roll += -(GetKeyState(VK_DOWN) & 0x80)*0.0001 + (GetKeyState(VK_UP) & 0x80)*0.0001;
	D3DXMatrixRotationY(&yaw_, Yaw);
	gazePoint_ = D3DXVECTOR3(0, Roll, 10);
	D3DXVec3TransformCoord(&gazePoint_, &gazePoint_, &yaw_);

	movePow_.x += -(GetKeyState('A') & 0x80)*0.001 + (GetKeyState('D') & 0x80)*0.001;
	movePow_.y += -(GetKeyState('Q') & 0x80)*0.001 + (GetKeyState('E') & 0x80)*0.001;
	movePow_.z += -(GetKeyState('S') & 0x80)*0.001 + (GetKeyState('W') & 0x80)*0.001;

	//���Z�b�g
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		movePow_ = D3DXVECTOR3(0, 48, -40);
		Yaw = 0;
		Roll = -11;
	}

}