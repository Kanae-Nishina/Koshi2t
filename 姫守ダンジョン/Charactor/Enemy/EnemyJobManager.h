//
//	@file	EnemyJobManager.h
//	@brief	�G���Ƃ̏���
//	@date	2016/11/13
//	@author	�g�z��R
//	@author	�m�ȍ��c

#pragma once
#include "./../Enemy/EnemyManager.h"


//	�E�ƊǗ��N���X
class EnemyJobManager :public EnemyManager
{
protected:

public:
	EnemyJobManager();
	virtual ~EnemyJobManager();
	virtual void Reset();
	virtual void CharaUpdate();
};

//	�X���C���N���X
class Slim :public EnemyJobManager
{
private:
	virtual void NormalAttack();
public:
	//Slim() {};
	virtual ~Slim() {};
};

//	�S�u�����N���X
class Goblin :public EnemyJobManager
{
private:
	virtual void NormalAttack();
public:
	virtual ~Goblin() {};
};


#include "./../Player/Job/WeaponBall.h"
//	�X�P���g���N���X
class Skeleton :public EnemyJobManager
{
private:
	virtual void NormalAttack();
	std::vector<WeaponBall*> atkList_;
public:
	virtual ~Skeleton() {};
	virtual void Reset();
	virtual void CharaRender();		//�`��

};