//
//	@file	Bomber.h
//	@brief	���e�m�N���X
//	@date	2016/11/21
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"
#include "../../../UI/TD_Graphics.h"
#include "../../../Effekseer/Effect.h"

//	���e�m�N���X
class Bomber :public JobManager
{
private:
	CD3DXMESH* bomb_;

	bool bombFlg_;	//���e�����������ǂ���
	bool invinsibleFlg_;	//���G�����ǂ���
	int invisibleCount_;
	int bombCount_;
	float bombScale_;
	//WeaponBall** bomb_;
	std::vector<WeaponBall*> bombList_;

	void InstanceWeapon();
	virtual void WeaponUpdate();
	virtual void Normal_Attack();
	virtual void Special_Attack();
	//virtual void MoveCharaHit();
	virtual void DeadSound();
	//virtual void Move(float speed);
	virtual void DamegeSound() {};

	//map<string, TD_Graphics*> bom_UI;

public:
	Bomber(CharaType charaType);
	virtual ~Bomber();
	//virtual const char* CharaInit(const char* fileName);
	virtual void Reset();
	virtual void Attack();
	//virtual void Move_Update();
	//virtual void DamageCalc(unsigned int atk);					//�_���[�W�v�Z
	virtual void CharaRender();
};