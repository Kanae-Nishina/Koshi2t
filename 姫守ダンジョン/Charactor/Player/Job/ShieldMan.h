//
//	@file	Shield.h
//	@brief	���m�N���X
//	@date	2016/11/21
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"
#include "../../../Effekseer/Effect.h"
//#include "../../../UI/TD_Graphics.h"

//	���m�N���X
class ShieldMan :public JobManager
{
private:
	bool spMoveFlg_;
	bool effectFlg_;
	D3DXVECTOR3 spMove_;
	CD3DXMESH* shield_;
	
	void Attack_Collision(float atk,float hitAngle);
	//void Normal_Attack_Collision();
	//void Special_Attack_Collision();
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void Move(float speed);
	//virtual void Move_Update();
	virtual void DeadSound();
	virtual void DamegeSound() {};

	/*map<string, TD_Graphics*> ShieldMan_UI;*/

public:
	ShieldMan(CharaType charaType);
	virtual ~ShieldMan();
	virtual void Reset();
	virtual void Attack();
	virtual void DamageCalc(unsigned int atk);	//�_���[�W�v�Z
	virtual void CharaRender();					//�`��
};
