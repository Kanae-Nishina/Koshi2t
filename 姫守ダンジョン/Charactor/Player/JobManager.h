//
//	@file	JobManager.h
//	@brief	�E�Ɩ��̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"

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
	//void Motion_Update();
public:
	JobManager(Controller controller);
	virtual ~JobManager();
	virtual void CharaUpdate();
};

//	���m�N���X
class SwordMan :public JobManager
{
protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	SwordMan(Controller controller);
};

//	�����m�N���X
class Witch :public JobManager
{
protected:	
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Witch(Controller controller);
};

//	���m�N���X
class ShieldMan :public JobManager
{
protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	ShieldMan(Controller controller);
};

//	���e�m�N���X
class Bomber :public JobManager
{
private:

protected:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(Controller controller);
};