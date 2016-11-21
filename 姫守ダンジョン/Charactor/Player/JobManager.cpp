//
//	@file	JobManager.h
//	@brief	�E�Ƃ��Ƃ̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#include "JobManager.h"

//	
//	@brief	�R���X�g���N�^
JobManager::JobManager(CharaType charaType)
	:timeCount_(0)
	, hit(0)
{
	atkNo_ = noAtk;
}

//
//	@brief	�f�X�g���N�^
JobManager::~JobManager()
{
}

//	
//	@brief	�p�����[�^�Z�b�g
void JobManager::SetParameter(JobParameter* param)
{
	memset(param_->name_,0, sizeof(param_->name_));
	strcpy_s(param_->name_, sizeof(param_->name_), param->GetName());

	param_->hp_ = param->GetHP();
	param_->normalAtk_ = param->GetNormalAtk();
	param_->specialAtk_ = param->GetSpAtk();
	param_->def_ = param->GetDefense();
	param_->specialAttackTime_ = param->GetWaitTime();
	param_->hp_ = param->GetChargeTime();
	param_->moveSpeed_ = param->GetMoveSpeed();
	param_->specialMoveSpeed_ = param->GetSpMoveSpeed();
	param_->weight_ = param->GetWeight();
	param_->attackReach_ = param->GetAttackReach_();
	param_->attackRange_ = param->GetAttackRange_();
	param_->scale_ = param->GetScale();

	ownWright_ = param_->weight_;
	hp_ = param_->hp_;
}

//
//	@brief	�L�����̍X�V
void JobManager::CharaUpdate()
{
	m_pD3dxMesh->m_pAnimController->AdvanceTime(0.1, NULL);
	//���ӂɂ���L�����`�F�b�N
	AroundCharaCheck();

	//�U��
	Attack();
	/*if (GamePad::checkInput(controller_, GamePad::InputName::A))
	{
		Attack();
	}*/

	//�P�Ă�
	if (GamePad::checkInput(charaType_, GamePad::InputName::B))
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

//
//	@brief	�p�����[�^�擾
//PlayerParameter JobManager::GetParam()const
//{
//	//return playerParm_;
//}
