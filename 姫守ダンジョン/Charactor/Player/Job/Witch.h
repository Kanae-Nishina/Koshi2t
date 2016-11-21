#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"
#include "./../Job/WeaponBall.h"

//	�����m�N���X
class Witch :public JobManager
{
	bool magicFlg_;	//�Z�����������ǂ���
	int magicBallCount_;
	//WeaponBall** magicBall_;
	std::vector<WeaponBall*> magicBall_;
private:
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Witch(CharaType charaType);
	virtual ~Witch();
	virtual void Attack();
	virtual void CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj);
};