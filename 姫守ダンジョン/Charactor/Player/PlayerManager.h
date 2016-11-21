//
//	@file	PlayerManager.h
//	@brief	�v���C���[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"

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

	//���[�V�����ԍ�
	enum MotionNo
	{
		waitM = 0,
		walkM,
		normalAtkM,
		specialAtkM,
		deadM,
		revivalM,
	};

	//�U����Ԕԍ�
	enum AttackState
	{
		noAtk = 0,	//�U�����Ă��Ȃ�
		waitAtk,	//�U���ҋ@
		normalAtk,	//�ʏ�U��
		charge,		//�`���[�W
		specialAtk,	//����U��
	};

	MotionNo motionNo_;		//���[�V�����ԍ�
	AttackState atkNo_;		//�U����Ԕԍ�
	Controller controller_;	//�R���g���[���[�ԍ�

	bool callFlg_;			//�P�Ăуt���O
	int attackCount_;		//�U���{�^���J�E���g

	virtual void Normal_Attack() = 0;	//�ʏ�U��
	virtual void Special_Attack() = 0;	//����U��
	//virtual void Attack();			//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	virtual void Motion_Update();		//���[�V�����X�V


public:
	PlayerManager() {};
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);	//�������Ɠǂݍ���
	void Revival();									//����
	//D3DXVECTOR3 Princess_Call();					//�P�Ă�
	bool GetAliveFlg()const;						//�����t���O�擾

	//�f�o�b�O�p
	int GetAtkCnt() { return attackCount_; };
	AttackState GetAtkState() { return atkNo_; };
	float GetYaw() { return m_Yaw; };
};