//
//	@file	JobManager.h
//	@brief	�G���Ƃ̏���
//	@date	2016/11/13
//	@outher	�g�z��R


#include "EnemyJobManager.h"

EnemyJobManager::EnemyJobManager()
{
}

EnemyJobManager::~EnemyJobManager()
{
}

void EnemyJobManager::CharaUpdate()
{
	moveAbleFlg_ = true;
	float speed = 0.05;
	MoveCharaHit();
	Move(speed);
}

//=======�X���C��=======//
//Slim::Slim()
//{
//}

void Slim::NormalAttack()
{
}