#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"
#include "./../Job/WeaponBall.h"

//	魔導士クラス
class Witch :public JobManager
{
	bool magicFlg_;	//技が発動中かどうか
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