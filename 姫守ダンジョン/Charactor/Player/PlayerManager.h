//
//	@file	PlayerManager.h
//	@brief	�v���C���[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"
#include "./../../DebugDraw/D3D11_TEXT.h"

enum Controller
{
	player1 = 0,
	player2,
	player3,
	player4,
};

class PlayerManager : public CharactorManager
{


protected:

	enum MotionNo
	{
		waitM=0,
		walkM,
		normalAtkM,
		spcialAtkM,
		deadM,
		revivalM,
	};

	MotionNo motionNo_;		//���[�V�����ԍ�
	Controller controller_;	//�R���g���[���[�ԍ�

	virtual void NormalAttack() = 0;	//�ʏ�U��
	virtual void SpecialAttack() = 0;	//����U��
	virtual void Attack();				//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	void Revival();						//����
public:
	PlayerManager() {};
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);
};