#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"

//	爆弾士クラス
class Bomber :public JobManager
{
private:
	bool bombFlg_;	//爆弾が発動中かどうか
	bool invincibleFlg_;	//無敵中かどうか
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
	virtual void DamageCalc(unsigned int atk);					//ダメージ計算
	virtual void CharaRender();
};