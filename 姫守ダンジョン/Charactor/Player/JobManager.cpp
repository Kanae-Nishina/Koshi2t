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
	, attackCount_(0)
{
	atkNo_ = noAtk;

	//�p�����[�^������
	param_ = new PlayerParameter;
}

//
//	@brief	�f�X�g���N�^
JobManager::~JobManager()
{
	delete param_;
	param_ = nullptr;
}

//	
//	@brief	�p�����[�^�Z�b�g
void JobManager::SetParameter(JobParameter* param)
{
	memset(param_->name_,0, sizeof(param_->name_));
	memcpy(param_->name_, param->GetName(), sizeof(param_->name_));

	param_->hp_ = param->GetHP();
	param_->normalAtk_ = param->GetNormalAtk();
	param_->specialAtk_ = param->GetSpAtk();
	param_->def_ = param->GetDefence();
	param_->chargeTime_ = param->GetChargeTime();
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
	hp_ = 1000;
}

//
//	@brief	�L�����̍X�V
void JobManager::CharaUpdate()
{
	//���ӂɂ���L�����`�F�b�N
	AroundCharaCheck();

	//���[�V�����ύX
	Motion_Update();

	//����
	if (aliveFlg_ == true)
	{
		//�ړ�
		float speed = param_->moveSpeed_;
		Move(speed);

		//�U��
		Attack();

		//�P�Ă�
		Princess_Call();
	}
	//���S
	else
	{
		Dead();

	}

	if (revivalFlg_ == true)
	{
		Revival();
	}

}

