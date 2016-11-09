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
}

//
//	@brief			�ړ�����
//	@param (speed)	�ړ����x
void PlayerManager::Move(float speed)
{
	//�X�e�B�b�N�̌X���擾
	D3DXVECTOR3 inputStick;
	inputStick.x = GamePad::getAnalogValue(controller_, GamePad::AnalogName::AnalogName_LeftStick_X);
	inputStick.z = GamePad::getAnalogValue(controller_, GamePad::AnalogName::AnalogName_LeftStick_Y);

	//��]����
	Rotation(inputStick);

	//�ړ�
	const float moveEpsilon = 0.2;	//���h�~�p
	float sp = 0;
	if (fabsf(inputStick.x) > moveEpsilon || fabsf(inputStick.z) > moveEpsilon)
	{
		sp = speed;
	}
	m_vPos += D3DXVECTOR3(inputStick.x*sp, 0, inputStick.z*sp);

}

//
//	@brief	���S����
void PlayerManager::Dead()
{

}

//
//	@brief	
void PlayerManager::Attack()
{
	NormalAttack();
	SpecialAttack();
}

//
//	@brief	�P�����グ
void PlayerManager::Queen_Lite()
{

}

//
//	@brief	����
void PlayerManager::Revival()
{
}