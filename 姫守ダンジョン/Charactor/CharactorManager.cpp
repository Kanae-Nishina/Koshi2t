//
//	@file	CharactorManager.h
//	@brief	�L�����N�^�[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c

#include "./CharactorManager.h"

//
//	@brief	�R���X�g���N�^
CharactorManager::CharactorManager()
	:opponentWeight_(0)
	, aroundCharaList_(0)
	, knockBackFlg_(0)
	,knockBackPos_(0,0,0)
	,knockBackDis_(0)
{
	collision_ = new Collision;
}

//
//	@brief	�f�X�g���N�^
CharactorManager::~CharactorManager()
{
	delete collision_;
	collision_ = nullptr;
}


//
//	@brief				�m�b�N�o�b�N����
//	@param (atkPos)		�U�������������n�_�̍��W
//	@param (distance)	�m�b�N�o�b�N���鋗��
void CharactorManager::KnockBack(D3DXVECTOR3 atkPos, float distance)
{
	//�����擾
	D3DXVECTOR3 dir = m_vPos - atkPos;

	//���K��
	D3DXVec3Normalize(&dir, &dir);

	//�p�x���Z�o
	float angle = (atan2(dir.z, dir.x)*-1) - (D3DX_PI / 2.0f);

	//�m�b�N�o�b�N�X�s�[�h
	const float knockBackSpeed = 1.0f;

	m_Dir = D3DXVECTOR3(knockBackSpeed*dir.x, 0, knockBackSpeed*dir.z);

	m_vPos += m_Dir;

	if (!collision_->CharaNear(m_vPos, atkPos, distance))
	{
		knockBackFlg_ = false;
	}
}

//
//	@brief			�L�����̉�]����
//	@param (dieVec)	��]�̌���
void CharactorManager::Rotation(D3DXVECTOR3 dirVec)
{
	//�p�x���Z�o
	float angel = (atan2(dirVec.z, dirVec.x)*-1) - (D3DX_PI / 2.0f);

	m_fYaw = angel;
}

//
//	@brief	�Ǌ���p�ړ�
void CharactorManager::SlipMove(D3DXVECTOR3 slipVec)
{
	m_Dir = slipVec;

}

//
//	@brief	�Î~�p
void CharactorManager::StopMove()
{
	m_Dir = D3DXVECTOR3(0, 0, 0);
}

//
//	@brief	�ړ��̍X�V
void CharactorManager::Move_Update()
{
	if (knockBackFlg_ == false)
	{
		m_vPos += m_Dir;
	}
	else
	{
		KnockBack(knockBackPos_,knockBackDis_);
	}
}

//
//	@brief				���ӂɂ���L�����N�^�[�����X�g�ɒǉ�
//	@param (charactor)	���ӂɂ���L�����N�^�[
void CharactorManager::SetAroundChara(CharactorManager* charactor)
{
	for (auto list : aroundCharaList_)
	{
		if (list == charactor)
		{
			return;
		}
	}

	aroundCharaList_.push_back(charactor);
}

//
//	@brief	���ӂɂ���L�����N�^�[���܂����ӂɂ��邩�ǂ����̃`�F�b�N
void CharactorManager::ArouncCharaCheck()
{
	float dist = 10;
	int count = 0;
	for (auto list : aroundCharaList_)
	{
		if (!collision_->CharaNear(m_vPos, list->m_vPos, dist))
		{
			//���Ȃ�������폜
			aroundCharaList_.erase(aroundCharaList_.begin() + count);
			--count;

			if (aroundCharaList_.empty())
			{
				break;
			}
		}
		++count;
	}
}

//
//	@brief	�i�s�����ɂ���L�����N�^�[�̏d���Z�b�g
void CharactorManager::SetOppWeight(float weight)
{
	opponentWeight_ = weight;
}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void CharactorManager::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));

}
