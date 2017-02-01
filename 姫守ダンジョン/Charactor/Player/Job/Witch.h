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
#include "../../../UI/TD_Graphics.h"

//	�����m�N���X
class Witch :public JobManager
{
private:

	bool magicFlg_;	//�Z�����������ǂ���
	int magicBallCount_;
	float magicSpeed_;
	CD3DXMESH* magic_;
	WeaponBall* magicBall_;

	void InstanceMagicBall(float range,float atk,bool flg);
	//void RazorBeam();
	virtual void WeaponUpdate();
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void DeadSound();
	virtual void DamageSound();

	//map<string, TD_Graphics*> Witch_UI;

public:
	Witch(CharaType charaType);
	virtual ~Witch();
	//virtual const char* CharaInit(const char* fileName);
	virtual void Reset();
	virtual void Attack();
	virtual void CharaRender();
};