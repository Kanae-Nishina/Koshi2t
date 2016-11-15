//
//	@file	JobManager.h
//	@brief	�E�Ɩ��̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"



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