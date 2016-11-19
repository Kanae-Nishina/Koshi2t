//
//	@file	JobManager.h
//	@brief	�E�Ƃ��Ƃ̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#include "JobManager.h"

JobManager::JobManager(Controller controller)
	:timeCount_(0)
	,hit(0)
	//,mime_(player)
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
		callFlg_ = true;
		//Princess_Call();
	}

	//���[�V�����ύX
	Motion_Update();

	//�ړ�
	Move(0.1);
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
SwordMan::SwordMan(Controller controller) :JobManager(controller)
{
	controller_ = controller;
	col_ = new Collision();
}

//
//	@brief	�U��
void SwordMan::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A)
		|| GetKeyState('1') & 0x80)
	{
		++attackCount_;
		atkNo_ = normalAtk;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		//atkNo_ = noAtk;
		//Special_Attack();
	}
	else if (atkNo_ == charge)
	{
		attackCount_ = 0;
		atkNo_ = specialAtk;

	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = 40;

	if (inputTime < attackCount_)
	{
		atkNo_ = charge;
	}
	else if (atkNo_ == normalAtk)
	{
		Normal_Attack();
	}

	if (atkNo_ == specialAtk)
	{
		Special_Attack();
	}
}

//
//	@breif	�ʏ�U��
void SwordMan::Normal_Attack()
{
	Normal_Attack_Collision();
	timeEnd_ = 30;
	if (++timeCount_ > timeEnd_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		timeCount_ = 0;
		hit = 0;
	}
}

//
//	@brief	�ʏ�U�������蔻��
void SwordMan::Normal_Attack_Collision()
{
	float degree = D3DXToDegree(m_fYaw);

	if (!aroundCharaList_.empty())
	{
		for (auto chara : aroundCharaList_)
		{
			D3DXVECTOR3 vec = chara->m_vPos - m_vPos;
			float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
			angle = D3DXToDegree(angle);

			float hitAngle = 45;
			if (fabsf(degree - angle) <= 45)
			{
				hit = true;
			}
			else
			{
				hit = false;
			}
		}
	}
}

//
//	@brief	����U��
void SwordMan::Special_Attack()
{
	//atkNo_ = noAtk;
	timeEnd_ = 30;
	if (++timeCount_ > timeEnd_)
	{
		atkNo_ = noAtk;
		//attackCount_ = 0;
		timeCount_ = 0;
	}
}

//////////////////////////////////////////////
Witch::Witch(Controller controller) :JobManager(controller)
{
	controller_ = controller;
}

//
//	@brief	�U��
void Witch::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ != noAtk)
	{
		//unsigned int inputTime = playerParam_.chargeTime_;
		unsigned int inputTime = 40;
		if (1 < attackCount_&& attackCount_ < inputTime)
		{
			atkNo_ = normalAtk;
			Normal_Attack();
		}
		else if (inputTime < attackCount_)
		{
			atkNo_ = specialAtk;
			Special_Attack();
		}
	}
	else if (atkNo_ == noAtk)
	{
		attackCount_ = 0;
	}
	//char str[256];
	//sprintf(str, "A : %d", attackCount_);
	//debugText_->Render(str, 0, 10);
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

//
//	@brief	�U��
void ShieldMan::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ != noAtk)
	{
		//unsigned int inputTime = playerParam_.chargeTime_;
		unsigned int inputTime = 40;
		if (1 < attackCount_&& attackCount_ < inputTime)
		{
			atkNo_ = normalAtk,
				Normal_Attack();
		}
		else if (inputTime < attackCount_)
		{
			atkNo_ = specialAtk;
			Special_Attack();
		}
	}
	else if (atkNo_ == noAtk)
	{
		attackCount_ = 0;
	}
	//char str[256];
	//sprintf(str, "A : %d", attackCount_);
	//debugText_->Render(str, 0, 10);
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

//
//	@brief	�U��
void Bomber::Attack()
{
	if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		++attackCount_;
		atkNo_ = waitAtk;
	}
	else if (atkNo_ != noAtk)
	{
		//unsigned int inputTime = playerParam_.chargeTime_;
		unsigned int inputTime = 40;
		if (1 < attackCount_&& attackCount_ < inputTime)
		{
			atkNo_ = normalAtk,
				Normal_Attack();
		}
		else if (inputTime < attackCount_)
		{
			atkNo_ = specialAtk;
			Special_Attack();
		}
	}
	else if (atkNo_ == noAtk)
	{
		attackCount_ = 0;
	}
	//char str[256];
	//sprintf(str, "A : %d", attackCount_);
	//debugText_->Render(str, 0, 10);
}

void Bomber::Normal_Attack()
{
}

void Bomber::Special_Attack()
{
}