//
//	@file	JobManager.h
//	@brief	EΖΜ
//	@date	2016/11/10
//	@author	mΘc

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"
#include "./../../Mesh/CD3DXMESH.h"
#include "./Job/WeaponBall.h"
#include "./../../UI/TD_Graphics.h"

#define UI_SPACE	20		//vC[1ΖζΚ[ΜΤ
#define UI_INTERVAL	480		//UIΖUIΜΤu(CharaTypeΙζZ·ι)

//	EΖΗNX
class JobManager :public PlayerManager
{
protected:
	TD_Graphics* backUI_;
	TD_Graphics* jobMarkUI_;
	TD_Graphics* hpGageUI_;
	D3DXVECTOR2 backUIPos_;
	D3DXVECTOR2 jobUIPos_;
	D3DXVECTOR2 hpGazePos_;
	//unsigned int timeCount_;	//UΤ
	//unsigned int timeAtkEnd_;		//UIΉΤ
	int attackCount_;			//U{^JEg
	Collision* col_;

	void UIRender();
	virtual void WeaponUpdate() {};
public:
	JobManager(CharaType charaType);
	virtual ~JobManager();

	virtual void CharaUpdate();
	//template<class> p;
	//void SetParameter(JobParameter* param);
	//PlayerParameter GetParam()const;

	int GetAtkCnt() { return attackCount_; };

	//fobNp
	PlayerParameter* GetParam()const { return param_; };
};

