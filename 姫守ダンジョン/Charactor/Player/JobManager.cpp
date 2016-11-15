//
//	@file	JobManager.h
//	@brief	�E�Ƃ��Ƃ̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#include "JobManager.h"

JobManager::JobManager(Controller controller)
{
}

JobManager::~JobManager()
{
}


void JobManager::CharaUpdate()
{
	//�U��
	Attack();
	/*if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Attack();
	}*/
	
	//�P�Ă�
	if (GamePad::checkInput(controller_, GamePad::InputName::B))
	{
		Princess_Call();
	}

	//���[�V�����ύX
	Motion_Update();

	//�ړ�
	Move(0.5);
}

////
////	@brief	���[�V�����X�V
//void JobManager::Motion_Update()
//{
//	m_pAnimController->AdvanceTime(0.001, NULL);
//
//	//�U��
//	if (GamePad::checkInput(controller_, GamePad::InputName::A))
//	{
//		ChangeMotion(waitM);
//	}
//
//	//�P�Ă�
//	if (GamePad::checkInput(controller_, GamePad::InputName::B))
//	{
//		ChangeMotion(walkM);
//	}
//}

//////////////////////////////////////////////
SwordMan::SwordMan(Controller controller):JobManager(controller)
{
	controller_ = controller;
}

void SwordMan::Normal_Attack()
{
	atkNo_ = noAtk;
	
}

void SwordMan::Special_Attack()
{
	atkNo_ = specialAtk;
}

//////////////////////////////////////////////
Witch::Witch(Controller controller):JobManager(controller)
{
	controller_ = controller;
}

void Witch::Normal_Attack()
{

}

void Witch::Special_Attack()
{
}

///////////////////////////////////////////////
ShieldMan::ShieldMan(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}

void ShieldMan::Normal_Attack()
{
}

void ShieldMan::Special_Attack()
{
}

//////////////////////////////////////////////
Bomber::Bomber(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}
void Bomber::Normal_Attack()
{
}

void Bomber::Special_Attack()
{
}