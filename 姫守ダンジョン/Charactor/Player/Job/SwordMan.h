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
public:
	SwordMan(CharaType charaType);
	virtual ~SwordMan();
	virtual void Attack();
};