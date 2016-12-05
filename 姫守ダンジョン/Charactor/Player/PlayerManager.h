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
/* �����̕K�v����H */
struct PlayerParameter
{
	char name_[30];							//�E�Ɩ�
	unsigned int hp_;					//HP
	unsigned int normalAtk_;			//�ʏ�U����
	unsigned int specialAtk_;			//����U����
	unsigned int def_;					//�����
	unsigned int chainWeapon_;			//�A����ѓ���ݒu��
	unsigned int spChainWeapon_;		//���ꎞ�A����ѓ���ݒu��
	unsigned int specialAttackTime_;	//����U������
	unsigned int invisibleTime_;		//���G����
	unsigned int weaponDelTime_;		//��ѓ�����Ŏ���
	unsigned int chargeTime_;			//�`���[�W�^�C��
	float moveSpeed_;					//�ړ����x
	float specialMoveSpeed_;			//����ړ����x
	float weight_;						//�d��
	float attackReach_;					//�U�����[�`
	float attackRange_;					//�U���͈�
	float specialAtkRange_;				//����U�����͈�
	float scale_;						//�X�P�[��
	float knockbackSpeed_;				//�m�b�N�o�b�N������X�s�[�h
	float knockbackDist_;				//�m�b�N�o�b�N���鋗��
	float weaponScale_;					//��ѓ���T�C�Y
	float weaponHitReach_;				//��ѓ���Փ˔͈�
	float weaponDelDist_;				//��ѓ�����ŋ���
};

class PlayerManager : public CharactorManager
{
private:
protected:
	double callTiming_;		//�P���Ă񂾃N���b�N����


	//�U����Ԕԍ�
	enum AttackState
	{
		noAtk = 0,	//�U�����Ă��Ȃ�
		waitAtk,	//�U���ҋ@
		normalAtk,	//�ʏ�U��
		charge,		//�`���[�W
		specialAtk,	//����U��
	};

	AttackState atkNo_;		//�U����Ԕԍ�
	PlayerParameter* param_;

	bool revivalFlg_;		//�����t���O
	D3DXVECTOR3 callPos_;	//�ǂ񂾏u�Ԃ̍��W

	virtual void Normal_Attack() = 0;	//�ʏ�U��
	virtual void Special_Attack() = 0;	//����U��
	//virtual void Attack();			//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	void Revival();						//����
	virtual void DeadSound() {};			//���S���T�E���h

public:
	PlayerManager();
	virtual ~PlayerManager() {};

	virtual const char* CharaInit(const char* fileName);	//�������Ɠǂݍ���
	virtual void DamageCalc(unsigned int atk);		//�_���[�W�v�Z
	void Princess_Call();							//�P�Ă�
	void SetRevivalFlg();
	bool GetAliveFlg()const;						//�����t���O�擾
	double GetCallTiming()const;
	D3DXVECTOR3 GetCallPos()const;					//�Ă񂾏u�Ԃ̍��W�擾

	//�f�o�b�O�p
	//int GetAtkCnt() { return attackCount_; };
	AttackState GetAtkState() { return atkNo_; };
	float GetYaw() { return m_Yaw; };
};