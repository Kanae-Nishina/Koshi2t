//
//	@file	JobManager.h
//	@brief	�E�Ɩ��̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"

//	�p�����[�^
struct PlayerParameter
{
	char* name_;	//�E�Ɩ�
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//�ʏ�U����
	unsigned int specialAtk_;	//����U����
	unsigned int def_;			//�����
	unsigned int waitTime_;		//�ҋ@����
	float speed_;				//�ړ����x
	float weight_;				//�d��
	float chargeTime_;			//�`���[�W�^�C��
};

//	�E�ƊǗ��N���X
class JobManager :public PlayerManager
{
protected:
	unsigned int timeCount_;	//�U������
	unsigned int timeEnd_;		//�U���I������
	//void Motion_Update();

	Collision* col_;

public:
	JobManager(Controller controller);
	virtual ~JobManager();
	virtual void CharaUpdate();
};

//	���m�N���X
class SwordMan :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
	void Normal_Attack_Collision();
public:
	SwordMan(Controller controller);
	virtual void Attack();
	//�f�o�b�O�p
	float dist;
	D3DXVECTOR3 nor;
};

//	�����m�N���X
class Witch :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Witch(Controller controller);
	virtual void Attack();
};

//	���m�N���X
class ShieldMan :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	ShieldMan(Controller controller);
	virtual void Attack();
};

//	���e�m�N���X
class Bomber :public JobManager
{
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(Controller controller);
	virtual void Attack();
};