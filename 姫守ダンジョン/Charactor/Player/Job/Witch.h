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
private:
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