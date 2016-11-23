//
//	@file	JobManager.h
//	@brief	�E�Ɩ��̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"
#include "./../../Mesh/CD3DXMESH.h"
#include "./Job/WeaponBall.h"
#include "./../../Read/ParameterRead.h"


//	�E�ƊǗ��N���X
class JobManager :public PlayerManager
{
protected:
	unsigned int timeCount_;	//�U������
	unsigned int timeEnd_;		//�U���I������
	int attackCount_;			//�U���{�^���J�E���g
	

	//void Motion_Update();

	Collision* col_;

public:
	JobManager(CharaType charaType);
	virtual ~JobManager();
	virtual void CharaUpdate();
	//template<class> p;
	void SetParameter(JobParameter* param);
	//PlayerParameter GetParam()const;
	bool hit;//�f�o�b�O�p

	int GetAtkCnt() { return attackCount_; };

	//�f�o�b�N�p
	PlayerParameter* GetParam()const { return param_; };
};

