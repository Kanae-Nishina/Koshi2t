//
//	@file	JobManager.h
//	@brief	�G���Ƃ̏���
//	@date	2016/11/13
//	@outher	�g�z��R

#pragma once
#include "./../Enemy/EnemyManager.h"


//	�E�ƊǗ��N���X
class EnemyJobManager :public EnemyManager
{
public:
	EnemyJobManager();
	virtual ~EnemyJobManager();
	virtual void CharaUpdate();
};

//	�X���C���N���X
class Slim :public EnemyJobManager
{
protected:
	virtual void NormalAttack();
public:
	//Slim() {};
	virtual ~Slim() {};
};