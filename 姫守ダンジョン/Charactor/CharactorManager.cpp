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
{
}

//
//	@brief	�f�X�g���N�^
CharactorManager::~CharactorManager()
{
	
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
	D3DXVec3Normalize(&dir,&dir);

	//�p�x���Z�o
	float angle = (atan2(dir.z, dir.x)*-1) - (D3DX_PI / 2.0f);

	//�m�b�N�o�b�N�X�s�[�h
	const float knockBackSpeed = 2.0f;
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
	m_vPos += m_Dir;
}

//
//	@brief				���ӂɂ���L�����N�^�[�����X�g�ɒǉ�
//	@param (charactor)	���ӂɂ���L�����N�^�[
void CharactorManager::SetAroundChara(CharactorManager* charactor)
{
	aroundCharaList_.push_back(charactor);
}

//
//	@brief	�i�s�����ɂ���L�����N�^�[�̏d���Z�b�g
void CharactorManager::SetOppWeight(float weight)
{
	opponentWeight_ = weight;
}

//
//	@brief				�ǂɂԂ����Ă��邩�ǂ����̃t���O�X�V
//	@param (wallHitFlg)	�ǂƂ̏Փ˔���
void CharactorManager::SetHitWall(bool wallHitFlg)
{
	hitWall_ = wallHitFlg;
}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void CharactorManager::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));

}
