//
//	@file	PlayerManager.h
//	@brief	�v���C���[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c
#pragma once
#include "./../CharactorManager.h"
#include "./GamePad.h"

class PlayerManager : public CharactorManager
{
protected:
	enum Controller
	{
		player1=0,
		player2,
		player3,
		player4,
	};
	Controller controller_;

	virtual void NormalAttack() = 0;	//�ʏ�U��
	virtual void SpecialAttack() = 0;	//����U��
	virtual void Attack();				//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	virtual void Motion_Update() {};	//���[�V�����X�V
	void Queen_Lite();					//�P�����グ
	void Revival();						//����
public:
	PlayerManager();
	virtual ~PlayerManager() {};
};