#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"


//	���m�N���X
class ShieldMan :public JobManager
{
private:
	bool spMoveFlg_;
	D3DXVECTOR3 spMove_;
	void Normal_Attack_Collision();
	void Special_Attack_Collision();
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
	virtual void Move_Update();
public:
	ShieldMan(CharaType charaType);
	virtual ~ShieldMan();
	virtual void Attack();
	virtual void DamageCalc(unsigned int atk);					//�_���[�W�v�Z
};
