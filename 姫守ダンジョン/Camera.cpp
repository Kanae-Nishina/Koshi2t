//
//	@file	Camera.cpp
//	@brief	�J�����֘A
//	@date	2016/11/08
//	@author	�m�ȍ��c

#include "Camera.h"

D3DXMATRIX Camera::mView_;
D3DXMATRIX Camera::mProj_;

//
//	@brief	�R���X�g���N�^
Camera::Camera()
	:titleCmeraSpeed_(0.1)
	, mainCameraSpeedF_(0.05)
	, mainCameraSpeedS_(0.4)
	, zoom_(6)
{
	firstMovePos_ =D3DXVECTOR3(0, 33.6, -41.53);
	firstGazePos_ =D3DXVECTOR3(0, 0, -12);
	mainDist_ = 20;
}

//
//	@brief	�f�X�g���N�^
Camera::~Camera()
{
}

//
//	@brief	���C���Q�[���J�n������X�V
bool Camera::Main_Start_FirstUpdate()
{
	static bool nextMoveFlg = false;
	float speed = mainCameraSpeedF_;
	gazePoint_ = D3DXVECTOR3(movePow_.x, movePow_.y, movePow_.z + 1.0f);
	if (movePow_.x < 3.0f)
	{
		movePow_.x += speed;
	}
	else
	{
		return true;
	}

	return false;
}

//
//	@brief	���C���Q�[���J�n�X�V
bool Camera::Main_Start_SecondUpdate()
{
	float speed = mainCameraSpeedS_;
	D3DXVECTOR3 tempPos = movePow_;
	D3DXVECTOR3 tempGaze = gazePoint_;
	//�J�������W�ړ�
	//x���ړ�
	if (movePow_.x > firstMovePos_.x)
	{
		movePow_.x -= speed;
	}
	//y���ړ�
	if (movePow_.y < firstMovePos_.y)
	{
		movePow_.y += speed;
	}
	//z���ړ�
	if (movePow_.z > firstMovePos_.z)
	{
		movePow_.z -= speed;
	}
	gazePoint_ = firstGazePos_;
	if (tempPos == movePow_)
	{
		movePow_ = firstMovePos_;
		return true;
	}

	return false;
}

//
//	@brief	���C���V�[���Q�[�����X�V
void Camera::Main_Game_Update()
{
	static float x = movePow_.x;
	movePow_.x = gazePoint_.x;
	movePow_.z = gazePoint_.z - mainDist_;
	x = movePow_.x;
}

//
//	@brief			�^�C�g���X�V
//	@param(radius)	��]�p�x
void Camera::TitleUpdate(float radius)
{
	static float degree = -100;
	float radian = D3DX_PI / 180 * degree;
	movePow_.x = gazePoint_.x + radius*cosf(radian);
	movePow_.z = gazePoint_.z + radius*sinf(radian);
	degree += titleCmeraSpeed_;
}

//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Camera::Render()
{
	//�r���[�g�����X�t�H�[��
	D3DXVECTOR3 camPos = movePow_;
	D3DXVECTOR3 lookPos = gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu

	D3DXMatrixTranslation(&tran_, 0, 0, 0);
	D3DXMatrixRotationY(&yaw_, 0);
	oriMat_ = yaw_*tran_;

	D3DXVec3TransformCoord(&camPos, &camPos, &oriMat_);
	D3DXVec3TransformCoord(&lookPos, &lookPos, &oriMat_);

	D3DXMatrixLookAtLH(&mView_, &camPos, &lookPos, &vUpVec);

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMatrixPerspectiveFovLH(&mProj_, D3DX_PI / zoom_, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);
}

//
//	@brief	�f�o�b�O�p�J�����ړ�	
void Camera::DebugMove()
{
	static float Yaw = 0, Roll = -23;
	Yaw += -(GetKeyState(VK_LEFT) & 0x80)*0.0005 + (GetKeyState(VK_RIGHT) & 0x80)*0.0005;
	Roll += -(GetKeyState(VK_DOWN) & 0x80)*0.001 + (GetKeyState(VK_UP) & 0x80)*0.001;
	D3DXMatrixRotationY(&yaw_, Yaw);
	gazePoint_ = D3DXVECTOR3(0, Roll, 10);
	D3DXVec3TransformCoord(&gazePoint_, &gazePoint_, &yaw_);

	movePow_.x += -(GetKeyState('A') & 0x80)*0.001 + (GetKeyState('D') & 0x80)*0.001;
	movePow_.y += -(GetKeyState('Q') & 0x80)*0.001 + (GetKeyState('E') & 0x80)*0.001;
	movePow_.z += -(GetKeyState('S') & 0x80)*0.001 + (GetKeyState('W') & 0x80)*0.001;

	//���Z�b�g
#if _DEBUG
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		movePow_ = D3DXVECTOR3(0, 0, 0); /*D3DXVECTOR3(0, 48, -40);*/
		Yaw = 0;
		Roll = -11;
	}
#endif

}