#pragma once
#include "./../../../Origin.h"
#include "./../JobManager.h"

//	���e�m�N���X
class Bomber :public JobManager
{
private:
	bool bombFlg_;	//�Z�����������ǂ���
	int bombCount_;
	float bombScale_;
	//WeaponBall** bomb_;
	std::vector<WeaponBall*> bomb_;
	std::vector<CharactorManager*> charaList_;
	virtual void Normal_Attack();
	virtual void Special_Attack();
public:
	Bomber(Controller controller);
	virtual void Attack();
	virtual void CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj);
	void SetForBombCharaList(std::vector<CharactorManager*> list);
};