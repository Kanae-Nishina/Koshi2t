//
//	@file	CharactorManager.h
//	@brief	�L�����N�^�[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c

#include "./CharactorManager.h"

//
//	@brief	�R���X�g���N�^
CharactorManager::CharactorManager()
	:opponentWeight_(1)
	, aroundCharaList_(0)
	, knockBackFlg_(0)
	, knockBackPos_(0, 0, 0)
	, knockBackDis_(0)
{
	collision_ = new Collision;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	//opponentWeight_ = 1;
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
	D3DXVECTOR3 dir = m_Pos - atkPos;

	//���K��
	D3DXVec3Normalize(&dir, &dir);

	//�p�x���Z�o
	float angle = (atan2(dir.z, dir.x)*-1) - (D3DX_PI / 2.0f);

	//�m�b�N�o�b�N�X�s�[�h
	const float knockBackSpeed = 1.0f;

	m_Dir = D3DXVECTOR3(knockBackSpeed*dir.x, 0, knockBackSpeed*dir.z);

	m_Pos += m_Dir;

	if (!collision_->CharaNear(m_Pos, atkPos, distance))
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

	m_Yaw = angel;
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
//	@brief			�m�b�N�o�b�N
//	@param (pos)	�U���҂̍��W
//	@param (dist)	�m�b�N�o�b�N����
void CharactorManager::SetKnockBack(D3DXVECTOR3 pos, float dist)
{
	knockBackFlg_ = true;
	knockBackPos_ = pos;
	knockBackDis_ = dist;
}

//
//	@brief	�ړ��̍X�V
void CharactorManager::Move_Update()
{
	if (aliveFlg_ == true)
	{
		if (knockBackFlg_ == false && moveAbleFlg_ == true)
		{
			m_Pos += m_Dir;
		}
		else if (knockBackFlg_ == true)
		{
			KnockBack(knockBackPos_, knockBackDis_);
		}
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
void CharactorManager::AroundCharaCheck()
{
	float dist = 10;
	int count = 0;

	for (size_t i = 0; i < aroundCharaList_.size(); i++)
	{
		//for (auto list : aroundCharaList_)
		//{
		if (!collision_->CharaNear(m_Pos, aroundCharaList_[count]->m_Pos, dist))
		{
			//���Ȃ�������폜
			aroundCharaList_.erase(aroundCharaList_.begin() + count);
			--count;

		}

		/*if (aroundCharaList_.empty())
		{
			break;
		}*/
		++count;
		//}
	}
}

//
//	@brief	�ړ������ɃL�����N�^�[�����邩
//	@note	�ړ������ɃL�����N�^�[��������A���̃L�����N�^�[�̏d�����擾
void CharactorManager::MoveCharaHit()
{
	float dist = 2;
	float degree = D3DXToDegree(m_Yaw);
	CharactorManager* opp = nullptr;
	for (auto c : aroundCharaList_)
	{
		if (collision_->CharaNear(m_Pos, c->m_Pos, dist))
		{
			D3DXVECTOR3 vec = c->m_Pos - m_Pos;
			float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
			angle = D3DXToDegree(angle);

			float hitAngle = 90 / 2;
			if (fabsf(degree - angle) <= hitAngle)
			{
				/*opponentWeight_ = c->ownWright_;*/
				opponentWeight_ = 0;
				opp = c;
			}
		}
	}
	if (opp == nullptr)
	{
		opponentWeight_ = 1;
	}
}

//
//	@brief	�i�s�����ɂ���L�����N�^�[�̏d���Z�b�g
void CharactorManager::SetOppWeight(float weight)
{
	opponentWeight_ = weight;
}

//
//	@brief	�L�����N�^�[�^�C�v�擾
CharaType CharactorManager::GetCharaType()const
{
	return charaType_;
}

//
//	@brief	�S�L�����N�^�[�Z�b�g
void CharactorManager::SetAllCharaList(std::vector<CharactorManager*> list)
{
	allCharaList_ = list;
}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void CharactorManager::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	m_View = mView;
	m_Proj = mProj;
	Render();
}
