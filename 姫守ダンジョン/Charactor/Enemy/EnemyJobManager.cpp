//
//	@file	JobManager.h
//	@brief	�G���Ƃ̏���
//	@date	2016/11/13
//	@outher	�g�z��R


#include "EnemyJobManager.h"

EnemyJobManager::EnemyJobManager()
{
	m_vPos = D3DXVECTOR3(0, -0.05, 0);
}

EnemyJobManager::~EnemyJobManager()
{
}

void EnemyJobManager::CharaUpdate()
{
	Move(0.05);
}

//=======�X���C��=======//
//Slim::Slim()
//{
//}

void Slim::NormalAttack()
{
}