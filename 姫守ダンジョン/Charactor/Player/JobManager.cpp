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

	//UI
	backUI_ = new TD_Graphics;
	backUIPos_ = D3DXVECTOR2(0 + charaType * UI_INTERVAL + UI_SPACE, 830);
	D3DXVECTOR2 backScale(461, 177);
	/*switch (charaType)
	{
	case Player1:
		backUI_->Init(L"./UI/UI_Tex/hp_frame.png", backUIPos_, backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Player2:
		backUI_->Init(L"./UI/UI_Tex/hp_frame2.png", backUIPos_, backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Player3:
		backUI_->Init(L"./UI/UI_Tex/hp_frame3.png", backUIPos_, backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case Player4:
		backUI_->Init(L"./UI/UI_Tex/hp_frame4.png", backUIPos_, backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	}*/
	backUI_->Init(L"./UI/UI_Tex/hp.png", backUIPos_, backScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	hpGageUI_ = new TD_Graphics;
	hpGazePos_ = D3DXVECTOR2(20 + charaType*UI_INTERVAL + UI_SPACE, 940);
	D3DXVECTOR2 hpScale(420, 60);
	hpGageUI_->Init(L"./UI/UI_Tex/HP_gage.png", hpGazePos_, hpScale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));

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

	delete backUI_;
	backUI_ = nullptr;

	delete hpGageUI_;
	hpGageUI_ = nullptr;
}

//
//	@brief	�L�����̍X�V
void JobManager::CharaUpdate()
{
	//��Ԕԍ��̍X�V
	spaceNo_ = collision_->SetSpaceNo(m_Pos,2);

	//���ӂɂ���L�����`�F�b�N
	AroundCharaCheck();


	//���X�s�[�h
	//motionSpeed_ = 0.05;
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
	else if(!revivalFlg_)
	{
		Dead();
	}

	//�_���[�W��H������Ƃ��R���g���[���̐U��
	if (damageFlg_)
	{
		GamePad::setVibration(charaType_);
	}
	else
	{
		GamePad::stopVibration(charaType_);
	}

	//��ѓ���̍X�V
	WeaponUpdate();

	//�h��
	if (revivalFlg_)
	{
		Revival();
	}
}

//
//	@brief	UI�`��
void JobManager::UIRender()
{
	D3DXVECTOR2 scale(1, 1);
	//jobMarkUI_->Render(jobUIPos_, scale, true);
	backUI_->Render(backUIPos_, scale, true);
	float hpX = (float)hp_ / (float)param_->hp_;
	scale = D3DXVECTOR2(hpX, 1);
	hpGageUI_->Render(hpGazePos_, scale, true);
}