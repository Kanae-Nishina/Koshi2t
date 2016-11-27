#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"

//	���e�m�N���X
class Bomber :public JobManager
{
private:
	bool bombFlg_;	//���e�����������ǂ���
	bool invinsibleFlg_;	//���G�����ǂ���
	int invisibleCount_;
	int bombCount_;
	float bombScale_;
	//WeaponBall** bomb_;
	std::vector<WeaponBall*> bomb_;
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(CharaType charaType);
	virtual ~Bomber();
	virtual void Attack();
	virtual void Move_Update();
	virtual void DamageCalc(unsigned int atk);					//�_���[�W�v�Z
	virtual void CharaRender();
};