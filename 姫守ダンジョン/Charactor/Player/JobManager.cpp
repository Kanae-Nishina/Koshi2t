//
//	@file	JobManager.h
//	@brief	�E�Ƃ��Ƃ̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#include "JobManager.h"

//	
//	@brief	�R���X�g���N�^
JobManager::JobManager(Controller controller)
	:timeCount_(0)
	, hit(0)
{
	atkNo_ = noAtk;
	SetParameter();
}

//
//	@brief	�f�X�g���N�^
JobManager::~JobManager()
{
}

//	
//	@brief	�p�����[�^�Z�b�g
void JobManager::SetParameter()
{
	paramRead_ = new ParameterRead;
	paramRead_->SetJobParameter("./ReadDate/JobParameterData.csv");

	//for(int i=0;i<paramRead_->get)
}

//
//	@brief	�L�����̍X�V
void JobManager::CharaUpdate()
{
	m_pD3dxMesh->m_pAnimController->AdvanceTime(0.1, NULL);
	//���ӂɂ���L�����`�F�b�N
	ArouncCharaCheck();

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

//
//	@brief	�p�����[�^�擾
//PlayerParameter JobManager::GetParam()const
//{
//	//return playerParm_;
//}
