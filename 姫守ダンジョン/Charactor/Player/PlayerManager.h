//
//	@file	PlayerManager.h
//	@brief	�v���C���[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c
#pragma once
#include <time.h>
#include "./../CharactorManager.h"
#include "./GamePad.h"

//	�p�����[�^
struct PlayerParameter
{
	char name_[30];				//�E�Ɩ�
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//�ʏ�U����
	unsigned int specialAtk_;	//����U����
	unsigned int def_;			//�����
	unsigned int chargeTime_;	//�`���[�W�^�C��
	float specialAttackTime_;	//�ҋ@����
	float moveSpeed_;			//�ړ����x
	float specialMoveSpeed_;	//����ړ����x
	float weight_;				//�d��
	float attackReach_;			//�U�����[�`
	float attackRange_;			//�U���͈�
	float scale_;				//�X�P�[��
};

class PlayerManager : public CharactorManager
{
private:
	double callTiming_;		//�P���Ă񂾃N���b�N����
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
	PlayerParameter* param_;

	bool revivalFlg_;		//�����t���O

	virtual void Normal_Attack() = 0;	//�ʏ�U��
	virtual void Special_Attack() = 0;	//����U��
	//virtual void Attack();			//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	virtual void Motion_Update();		//���[�V�����X�V
	void Revival();						//����

public:
	PlayerManager();
	virtual ~PlayerManager() {};

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);	//�������Ɠǂݍ���
	virtual void DamageCalc(unsigned int atk);					//�_���[�W�v�Z
	void Princess_Call();										//�P�Ă�
	void SetRevivalFlg();
	bool GetAliveFlg()const;						//�����t���O�擾
	double GetCallTiming()const;

	//�f�o�b�O�p
	//int GetAtkCnt() { return attackCount_; };
	AttackState GetAtkState() { return atkNo_; };
	float GetYaw() { return m_Yaw; };
};