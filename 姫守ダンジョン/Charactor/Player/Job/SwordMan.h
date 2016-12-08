//
//	@file	SwordMan.h
//	@brief	���m�N���X
//	@date	2016/11/21
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#pragma once
#include "./../../../Origin.h"
#include "./../../Player/JobManager.h"

//	���m�N���X
class SwordMan :public JobManager
{
private:
	void Normal_Attack_Collision();
	void Special_Attack_Collision();
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void DeadSound();
	virtual void DamageSound();
public:
	SwordMan(CharaType charaType);
	virtual ~SwordMan();
	virtual void Reset();
	virtual void Attack();
};