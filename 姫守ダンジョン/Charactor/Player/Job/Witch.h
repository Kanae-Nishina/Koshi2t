//
//	@file	Witch.h
//	@brief	�����m�N���X
//	@date	2016/11/21
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"
#include "./../Job/WeaponBall.h"

//	�����m�N���X
class Witch :public JobManager
{
	bool magicFlg_;	//�Z�����������ǂ���
	int magicBallCount_;
	WeaponBall* magic_;
	std::vector<WeaponBall*> magicBall_;

	void InstanceMagicBall(int count);
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void DeadSound();
	virtual void DamageSound();
public:
	Witch(CharaType charaType);
	virtual ~Witch();
	virtual const char* CharaInit(const char* fileName);
	virtual void Reset();
	virtual void Attack();
	virtual void CharaRender();
};