//
//	@file	EnemyManager.cpp
//	@brief	�G�l�~�[�Ǘ��N���X
//	@date	2016/11/13
//	@outher�@�g�z��R

#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	charaType_ = Enemy;
	m_Pos = { 0,0,0 };
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	opponentWeight_ = 1;
	//targetPos_ = D3DXVECTOR3(0, 0, 0);
	collision_ = new Collision;
	param_ = new EnemyParam;
}

EnemyManager::~EnemyManager()
{
	delete collision_;
	collision_ = nullptr;
	//delete motion_;
	//motion_ = nullptr;
}

//
//	@brief						X�t�@�C���ǂݍ���
//	@param (m_hWnd)				�E�B���h�E�n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
//	@param (fileName)			�ǂݍ��ރL������
const char* EnemyManager::CharaInit(const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Enemy/");
	strcat_s(FileName, sizeof(FileName), fileName);

	return FileName;
	//CreateFromX(FileName);
	//m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	//m_Pos = D3DXVECTOR3(0, 0, 0);
}

//
//	@brief	�p�����[�^�Z�b�g
void EnemyManager::SetParameter(EnemyParameter* param)
{
	memset(param_->name_, 0, sizeof(param_->name_));
	memcpy(param_->name_, param->GetName(), sizeof(param_->name_));

	param_->hp_ = param->GetHP();
	param_->atk_ = param->GetAtk();
	param_->def_ = param->GetDefence();
	param_->moveSpeed_ = param->GetMoveSpeed();
	param_->weight_ = param->GetWeight();
	param_->attackReach_ = param->GetAttackReach();
	param_->scale_ = param->GetScale();

	ownWright_ = param_->weight_;
	hp_ = param_->hp_;

	//hp_ = 10000;
}

//
//	@brief�@			�^�[�Q�b�g�ݒ�
//	@param (chara)		�^�[�Q�b�g�ɂ���L����
void EnemyManager::SetTarget(CharactorManager* chara)
{
	targetChar_ = chara;
	targetPos_ = targetChar_->m_Pos;
}

//
//	@brief�@				�^�[�Q�b�g�̍X�V
//	@param (chara)			�v���C���[
//	@param (princess)		�P
void EnemyManager::Target_Update(CharactorManager * chara, CharactorManager * princess)
{
	CharactorManager* temp = chara;
	float dist = 5;

	if (targetChar_->GetCharaType() != temp->GetCharaType())
	{
		temp = targetChar_;
	}

	//���݂̃^�[�Q�b�g���P
	if (targetChar_->GetCharaType() == princess->GetCharaType())
	{
		if (collision_->CharaNear(m_Pos, chara->m_Pos, dist))
		{
			temp = chara;
		}
	}

	//�^�[�Q�b�g������ł���
	if (!temp->GetAliveFlg())
	{
		temp = princess;
	}

	//�^�[�Q�b�g�̍X�V
	SetTarget(temp);
}

//
//	@brief�@			�^�[�Q�b�g�|�W�V�����̍X�V
//	@param (position)	���W
void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
{
	////���݂̃^�[�Q�b�g�ƃ`�F�b�N����v���C���[����v���邩
	//if (targetChar_->GetCharaType() == checkChar->GetCharaType())
	//{
	//	//�`�F�b�N����(���݃^�[�Q�b�g�̃v���C���[�j���������Ă��邩
	//	if (checkChar->GetAliveFlg())
	//	{
	//		//�^�[�Q�b�g�X�V
	//		targetChar_ = checkChar;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//	else
	//	{
	//		//�^�[�Q�b�g��P�ɕύX
	//		targetChar_ = princess;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//}
	//else if (targetChar_->GetCharaType() == princess->GetCharaType()/* || targetChar_ == nullptr*/)       //���݂̃^�[�Q�b�g���P
	//{
	//	//�߂��ɐ����Ă���v���C���[�����邩�ǂ���(�`�F�b�N����v���C���[�������Ă��� ���� ���������ȓ�)
	//	if (checkChar->GetAliveFlg() && collision_->CharaNear(m_Pos, checkChar->m_Pos, 50.0))
	//	{
	//		//�^�[�Q�b�g���v���C���[�ɕύX
	//		targetChar_ = checkChar;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//	else         //�߂��ɐ����Ă���v���C���[�����Ȃ�
	//	{
	//		//�^�[�Q�b�g�X�V
	//		targetChar_ = princess;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//}

	////if (!targetChar_->GetAliveFlg())
	////{
	////	targetChar_ = princess;
	////	targetPos_ = targetChar_->m_Pos;
	////}
}

//
//	@brief			�ړ�����
//	@param (speed)	�ړ����x
void EnemyManager::Move(float speed)
{
	D3DXVECTOR3 E_Lock;
	E_Lock.x = targetPos_.x - m_Pos.x;
	E_Lock.z = targetPos_.z - m_Pos.z;

	D3DXVec3Normalize(&E_Lock, &E_Lock);

	//��]����
	Rotation(E_Lock);

	//�����Ă���p�x����P�ʃx�N�g�����擾
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-1, 0, cosf(m_Yaw)*-1);
	//D3DXVECTOR3 vec = E_Lock;
	float sp = speed;
	//opponentWeight_ = 1;
	m_Dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);

	//if (motionNo_ != 0)
	//{
	//	motionNo_ = 0;
	//	m_pD3dxMesh->ChangeAnimSet(0);
	//	motionSpeed_ = 0.01;
	//}

}

//
//	@brief	�_���[�W�v�Z
void EnemyManager::DamageCalc(unsigned int atk)
{

	float damage = atk / (1 + ((float)param_->def_ / 100));

	if (hp_ <= damage)
	{
		hp_ = 0;
		aliveFlg_ = false;
	}
	else
	{
		hp_ -= damage;
	}
}

//
//	@brief	���S����
void EnemyManager::Dead()
{
}

//
//	@brief	�G�ʏ�U��
void EnemyManager::Attack()
{
	float atkableDist = 2;//param_->attackReach_;
	int time = 3;

	if (collision_->CharaNear(m_Pos, targetPos_, atkableDist))
	{
		if (++atkWaitTime_ % (FPS*time) == 0)
		{
			moveAbleFlg_ = false;
			NormalAttack();
		}
		else
		{
			moveAbleFlg_ = true;
		}
	}
	else
	{
		moveAbleFlg_ = true;
		atkWaitTime_ = 0;
	}
}
