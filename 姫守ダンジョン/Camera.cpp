//
//	@file	Camera.cpp
//	@brief	�J�����֘A
//	@date	2016/11/08
//	@author	�m�ȍ��c

#include "Camera.h"

D3DXMATRIX Camera::mView_;
D3DXMATRIX Camera::mProj_;
//D3DXVECTOR3 Camera::movePow_;
//D3DXVECTOR3 Camera::gazePoint_;

//
//	@brief	�R���X�g���N�^
Camera::Camera()
{

	zoom = 6;
	farPlayerPos_ = movePow_;
	//dist_ = zoom;
	dist_ = 0;
	temp_ = 27;
}

//
//	@brief	�f�X�g���N�^
Camera::~Camera()
{
}

//
//	@brief	�v���C���[�|�W�V�����Z�b�g	
void Camera::SetPlayerPos(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 pPos = pos;
	float distx = powf(pos.x - gazePoint_.x, 2) + powf(pos.z - gazePoint_.z, 2);

	if (dist_ <= distx)
	{
		farPlayerPos_ = pos;
		dist_ = distx;
		//temp_ = dist_;
	}
}

//
//	@brief	���C���V�[���Q�[���J�n���X�V
bool Camera::Main_Start_FirstUpdate()
{
	//movePow_ = D3DXVECTOR3(0, 45, -45);
	static bool nextMoveFlg = false;
	float speed = 0.05;
	//if (!nextMoveFlg)
	//{
	gazePoint_ = D3DXVECTOR3(movePow_.x, movePow_.y, movePow_.z + 1.0f);
	if (movePow_.x < 3.0f)
	{
		movePow_.x += speed;
	}
	else
	{
		return true;
	}
	//}
	//else
	//{
	//	D3DXVECTOR3 firstMovePos(0, 45, -45);
	//	D3DXVECTOR3 firstGazePos(0, 0, -12);
	//	speed = 0.4;
	//	//�J�������W�ړ�
	//	//x���ړ�
	//	if (movePow_.x > firstMovePos.x)
	//	{
	//		movePow_.x -= speed;
	//	}
	//	//y���ړ�
	//	if (movePow_.y < firstMovePos.y)
	//	{
	//		movePow_.y += speed;
	//	}
	//	//z���ړ�
	//	if (movePow_.z > firstMovePos.z)
	//	{
	//		movePow_.z -= speed;
	//	}
	//	//gazePoint_ = firstGazePos;
	//	//�����_���W�ړ�
	//	//x���ړ�
	//	speed = 0.1;
	//	if (gazePoint_.x > firstGazePos.x)
	//	{
	//		gazePoint_.x -= speed;
	//	}
	//	//y���ړ�
	//	if (gazePoint_.y > firstGazePos.y)
	//	{
	//		gazePoint_.y -= speed;
	//	}
	//	//z���ړ�
	//	if (gazePoint_.z > firstGazePos.z)
	//	{
	//		gazePoint_.z -= speed;
	//	}
	//}

	return false;
}

bool Camera::Main_Start_SecondUpdate()
{
	D3DXVECTOR3 firstMovePos(0, 40, -40);
	D3DXVECTOR3 firstGazePos(0, 0, -12);
	float speed = 0.4;
	D3DXVECTOR3 tempPos = movePow_;
	D3DXVECTOR3 tempGaze = gazePoint_;
	//�J�������W�ړ�
	//x���ړ�
	if (movePow_.x > firstMovePos.x)
	{
		movePow_.x -= speed;
	}
	//y���ړ�
	if (movePow_.y < firstMovePos.y)
	{
		movePow_.y += speed;
	}
	//z���ړ�
	if (movePow_.z > firstMovePos.z)
	{
		movePow_.z -= speed;
	}
	//gazePoint_ = firstGazePos;
	//�����_���W�ړ�
	//x���ړ�
	speed = 0.1;
	if (gazePoint_.x > firstGazePos.x)
	{
		gazePoint_.x -= speed;
	}
	//y���ړ�
	if (gazePoint_.y > firstGazePos.y)
	{
		gazePoint_.y -= speed;
	}
	//z���ړ�
	if (gazePoint_.z > firstGazePos.z)
	{
		gazePoint_.z -= speed;
	}

	if (tempPos == movePow_ && tempGaze == gazePoint_)
	{
		movePow_ = firstMovePos;
		gazePoint_ = firstGazePos;
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
	movePow_.z = gazePoint_.z - 40;
	float y = x - movePow_.x;
	movePow_.y += y;
	x = movePow_.x;
}

void Camera::TitleUpdate(float radius)
{
	//static float move = 0;
	//movePow_.x += cosf(move);
	//movePow_.z += sinf(move);
	//move += 0.01;
	static float degree = -100;
	float radian = D3DX_PI / 180 * degree;
	movePow_.x = gazePoint_.x + radius*cosf(radian);
	movePow_.z = gazePoint_.z + radius*sinf(radian);
	degree += 0.1f;
}

//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Camera::Render()
{
	//�r���[�g�����X�t�H�[�� �J�������L�����̌��ɔz�u���邾��
	D3DXVECTOR3 camPos = movePow_;
	D3DXVECTOR3 lookPos = gazePoint_;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu

	D3DXMatrixTranslation(&tran_, 0, 0, 0);
	D3DXMatrixRotationY(&yaw_, 0);
	//D3DXMatrixRotationZ(&pitch_, gazePoint_.z);
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