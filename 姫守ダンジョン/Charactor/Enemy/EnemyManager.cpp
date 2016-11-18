//
//	@file	EnemyManager.cpp
//	@brief	�G�l�~�[�Ǘ��N���X
//	@date	2016/11/13
//	@outher�@�g�z��R

#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	m_vPos = { 0,0,0 };
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
	if (FAILED(Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName)))
	{
		return;
	}
}

//
//	@brief�@			�^�[�Q�b�g�|�W�V�����̍X�V
//	@param (position)	���W
//void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
//{
//	/*if (targetObj_ != player)
//	{
//		float range = 1.0f;
//		double checkDist = range*range;
//		if (collision_->CharaNear(m_vPos,position,checkDist))
//		{
//			targetObj_ = player;
//		}
//		else
//		{
//			virPos = D3DXVECTOR3(0, 0, 0);
//		}
//	}
//	
//	targetPos_ = virPos;*/
//	//���݂̃^�[�Q�b�g�ƃ`�F�b�N����v���C���[����v���邩
//	if (targetChar_ == checkChar)
//	{
//		//�`�F�b�N����(���݃^�[�Q�b�g�̃v���C���[�j���������Ă��邩
//		if (checkChar->GetAliveFlg())
//		{
//			//�^�[�Q�b�g�X�V
//			targetChar_ = checkChar;
//		}
//		else        //����ǂ��[��
//		{
//			//�^�[�Q�b�g��P�ɕύX
//			targetChar_ = princess;
//		}
//	}
//	else if (targetChar_ == princess || targetChar_ == nullptr)       //���݂̃^�[�Q�b�g���P
//	{
//		//�߂��ɐ����Ƃ�v���C���[�����邩�ǂ���(�`�F�b�N����v���C���[�������Ă��� ���� ���������ȓ�)
//		if (checkChar->GetAliveFlg() && collision_->CharaNear(m_vPos, checkChar->m_vPos, 50.0))
//		{
//			//�^�[�Q�b�g���v���C���[�ɕύX
//			targetChar_ = checkChar;
//		}
//		else         //�߂��ɐ����Ƃ�v���C���[������񂪂�(�`�F�b�N����v���C���[�������Ă��Ȃ� ���� �����������)
//		{
//			//�^�[�Q�b�g�X�V
//			targetChar_ = princess;
//		}
//	}
//}

//
//	@brief			�ړ�����
//	@param (speed)	�ړ����x
void EnemyManager::Move(float speed)
{
	D3DXVECTOR3 E_Lock;
	E_Lock.x = targetPos_.x - m_vPos.x;
	E_Lock.z = targetPos_.z - m_vPos.z;

	//��]����
	Rotation(E_Lock);
	float sp = speed;
	
	m_Dir += D3DXVECTOR3(E_Lock.x*sp,0, E_Lock.z*sp);
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
