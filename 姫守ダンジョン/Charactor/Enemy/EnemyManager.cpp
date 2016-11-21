//
//	@file	EnemyManager.cpp
//	@brief	�G�l�~�[�Ǘ��N���X
//	@date	2016/11/13
//	@outher�@�g�z��R

#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	m_Pos = { 0,0,0 };
	//targetPos_ = D3DXVECTOR3(0, 0, 0);
	collision_ = new Collision;
}

EnemyManager::~EnemyManager()
{
	delete collision_;
	collision_ = nullptr;
}

//
//	@brief						X�t�@�C���ǂݍ���
//	@param (m_hWnd)				�E�B���h�E�n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
//	@param (fileName)			�ǂݍ��ރL������
void EnemyManager::CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Enemy/");
	strcat_s(FileName, sizeof(FileName), fileName);
	CD3DXSKINMESH_INIT si;
	si.hWnd = m_hWnd;
	si.pDevice = m_pDevice;
	si.pDeviceContext = m_pDeviceContext;
	Init(&si);
	CreateFromX(FileName);
	m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
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
	if (targetChar_->GetCharaType() != temp->GetCharaType())
	{
		temp = targetChar_;
	}
	//���݂̃^�[�Q�b�g���P
	if (targetChar_->GetCharaType() == princess->GetCharaType())
	{
		temp = chara;
	}
	////���݂̃^�[�Q�b�g������ł���
	//if (!targetChar_->GetAliveFlg())
	//{
	//	targetChar_ = princess;
	//}

	SetTarget(temp);
}

//
//	@brief�@			�^�[�Q�b�g�|�W�V�����̍X�V
//	@param (position)	���W
void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
{
	/*if (targetObj_ != player)
	{
		float range = 1.0f;
		double checkDist = range*range;
		if (collision_->CharaNear(m_Pos,position,checkDist))
		{
			targetObj_ = player;
		}
		else
		{
			virPos = D3DXVECTOR3(0, 0, 0);
		}
	}
	
	targetPos_ = virPos;*/
	//���݂̃^�[�Q�b�g�ƃ`�F�b�N����v���C���[����v���邩
	if (targetChar_ == checkChar)
	{
		//�`�F�b�N����(���݃^�[�Q�b�g�̃v���C���[�j���������Ă��邩
		if (checkChar->GetAliveFlg())
		{
			//�^�[�Q�b�g�X�V
			targetChar_ = checkChar;
			targetPos_ = targetChar_->m_Pos;
		}
		else        //����ǂ��[��
		{
			//�^�[�Q�b�g��P�ɕύX
			targetChar_ = princess;
			targetPos_ = targetChar_->m_Pos;
		}
	}
	else if (targetChar_ == princess || targetChar_ == nullptr)       //���݂̃^�[�Q�b�g���P
	{
		//�߂��ɐ����Ƃ�v���C���[�����邩�ǂ���(�`�F�b�N����v���C���[�������Ă��� ���� ���������ȓ�)
		if (checkChar->GetAliveFlg() && collision_->CharaNear(m_Pos, checkChar->m_Pos, 50.0))
		{
			//�^�[�Q�b�g���v���C���[�ɕύX
			targetChar_ = checkChar;
			targetPos_ = targetChar_->m_Pos;
		}
		else         //�߂��ɐ����Ƃ�v���C���[������񂪂�(�`�F�b�N����v���C���[�������Ă��Ȃ� ���� �����������)
		{
			//�^�[�Q�b�g�X�V
			targetChar_ = princess;
			targetPos_ = targetChar_->m_Pos;
		}
	}
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
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);

	float sp = speed;
	
	m_Dir = D3DXVECTOR3(vec.x*sp,0, vec.z*sp);
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
	NormalAttack();
}
