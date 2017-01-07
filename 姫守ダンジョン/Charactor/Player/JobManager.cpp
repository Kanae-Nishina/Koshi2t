//
//	@file	JobManager.cpp
//	@brief	�E�Ƃ��Ƃ̏���
//	@date	2016/11/10
//	@author	�m�ȍ��c

#include "JobManager.h"

//	
//	@brief	�R���X�g���N�^
JobManager::JobManager(CharaType charaType)
	: attackCount_(0)
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

	delete collision_;
	collision_ = nullptr;
}

//
//	@brief	�L�����̍X�V
void JobManager::CharaUpdate()
{
	//��Ԕԍ��̍X�V
	spaceNo_ = collision_->SetSpaceNo(m_Pos);

	//���ӂɂ���L�����`�F�b�N
	AroundCharaCheck();


	//���X�s�[�h
	//motionSpeed_ = 0.05;
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);
	//Motion_Update();

	//����
	if (aliveFlg_ == true)
	{
		//�ړ�
		if (moveAbleFlg_ == true)
		{
			float speed = param_->moveSpeed_;
			Move(speed);
		}

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

	//��ѓ���̍X�V
	WeaponUpdate();

	//�h��
	if (revivalFlg_ == true)
	{
		Revival();
	}
}

