//
//	@file	PlayerManager.cpp
//	@brief	�v���C���[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c

#include "PlayerManager.h"

//
//	@brief	�R���X�g���N�^
PlayerManager::PlayerManager()
{
	revivalFlg_ = false;
	callTiming_ = 0;
}

//
//	@brief						X�t�@�C���ǂݍ���
//	@param (m_hWnd)				�E�B���h�E�n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
//	@param (fileName)			�ǂݍ��ރL������
void PlayerManager::CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Player/");
	strcat_s(FileName, sizeof(FileName), fileName);
	CD3DXSKINMESH_INIT si;
	si.hWnd = m_hWnd;
	si.pDevice = m_pDevice;
	si.pDeviceContext = m_pDeviceContext;
	Init(&si);
	CreateFromX(FileName);
	m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	//ownWright_ = 0.001f;
}

//
//	@brief			�ړ�����
//	@param (speed)	�ړ����x
void PlayerManager::Move(float speed)
{
	//�X�e�B�b�N�̌X���擾
	D3DXVECTOR3 inputStick;
	inputStick.x = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.z = GamePad::getAnalogValue(charaType_, GamePad::AnalogName::AnalogName_LeftStick_Y);

	//��]����
	const float rotEpsilon = 0.3;
	if (fabsf(inputStick.x) > rotEpsilon || fabsf(inputStick.z) > rotEpsilon)
	{
		Rotation(inputStick);
	}


	//�ړ�
	const float moveEpsilon = 0.2;	//���h�~�p
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		sp = speed;
		if (motionNo_ != walkM)
		{
			motionNo_ = walkM;
			m_pD3dxMesh->ChangeAnimSet(walkM);
			//ChangeMotion(waitM);
		}
	}
	else
	{
		if (motionNo_ != waitM)
		{
			motionNo_ = waitM;
			m_pD3dxMesh->ChangeAnimSet(0);
			//ChangeMotion(walkM);
		}
	}

	//opponentWeight_ = 1;
	MoveCharaHit();

	m_Dir = D3DXVECTOR3(inputStick.x*sp * opponentWeight_, 0, inputStick.z*sp * opponentWeight_);
	//m_vPos += D3DXVECTOR3(inputStick.x*sp - opponentWeight_, 0, inputStick.z*sp - opponentWeight_);

	GamePad::update();

	//m_Dir = D3DXVECTOR3(m_AxisX.x, m_AxisY.y, m_AxisZ.z);
	//m_Dir = D3DXVECTOR3(m_Move.x, 0, m_Move.z);
}

//
//	@brief	�_���[�W�v�Z
void PlayerManager::DamageCalc(unsigned int atk)
{
	float damage = atk / (1 + ((float)param_->def_ / 100));
	hp_ -= damage;

	if (hp_ <= 0)
	{
		hp_ = 0;
		aliveFlg_ = false;
	}

}

//
//	@brief	���S����
void PlayerManager::Dead()
{
	//aliveFlg_ = false;
}

//
//	@brief	���[�V�����X�V
void PlayerManager::Motion_Update()
{
	const float speed = 0.01;
	m_pD3dxMesh->m_pAnimController->AdvanceTime(speed, NULL);

}


//
//	@brief	����
void PlayerManager::Revival()
{

	aliveFlg_ = true;
	hp_ = param_->hp_;
	revivalFlg_ = false;
}

//
//	@brief	�P�Ă�
void PlayerManager::Princess_Call()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::B))
	{
		moveAbleFlg_ = false;
		callTiming_ = clock();
	}
}

//
//	@breif	�����t���O�Z�b�g
void PlayerManager::SetRevivalFlg()
{
	revivalFlg_ = true;
}

//
//	@brief	�����t���O�擾
bool PlayerManager::GetAliveFlg()const
{
	return aliveFlg_;
}


//
//	@brief	�P���Ă񂾃N���b�N���Ԏ擾
double PlayerManager::GetCallTiming()const
{
	return callTiming_;
}