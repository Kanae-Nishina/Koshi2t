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

	delete motion_;
	motion_ = nullptr;
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
	param_->chainWeapon_ = param->GetChainWeapon();
	param_->spChainWeapon_ = param->GetSpChainWeapon();
	param_->specialAttackTime_ = param->GetSpAtkTime();
	param_->invisibleTime_ = param->GetInvisivleTime();
	param_->weaponDelTime_ = param->GetWeaponDelTime();
	param_->chargeTime_ = param->GetChargeTime();
	param_->moveSpeed_ = param->GetMoveSpeed();
	param_->specialMoveSpeed_ = param->GetSpMoveSpeed();
	param_->weight_ = param->GetWeight();
	param_->attackReach_ = param->GetAttackReach();
	param_->attackRange_ = param->GetAttackRange();
	param_->specialAtkRange_ = param->GetSpAtkRange();
	param_->scale_ = param->GetScale();
	param_->knockbackSpeed_ = param->GetKnockBackSpeed();
	param_->knockbackDist_ = param->GetKnockBackDist();
	param_->weaponScale_ = param->GetWeaponScale();
	param_->weaponHitReach_ = param->GetWeaponHitReach();
	param_->weaponDelDist_ = param->GetWeaponDelDist();

	m_Scale = D3DXVECTOR3(param_->scale_, param_->scale_, param_->scale_);
	ownWright_ = param_->weight_;
	hp_ = param_->hp_;
}

//
//	@brief	�L�����̍X�V
void JobManager::CharaUpdate()
{
	//���ӂɂ���L�����`�F�b�N
	AroundCharaCheck();

	m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);


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

