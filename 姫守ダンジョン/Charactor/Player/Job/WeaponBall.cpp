//
//	@file	WeaponBall.cpp
//	@brief	��ѓ���N���X
//	@date	2016/11/21
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#include "./WeaponBall.h"


//
//	@brief	��ѓ���R���X�g���N�^
WeaponBall::WeaponBall()
	:delCount_(0)
{
	weaponBall_ = new CD3DXMESH;
	creator_ = new CharactorCreator;
	weaponBall_->m_fScale = 0.5;
	delFlg_ = false;
	col_ = new Collision;
	effectflg_ = false;
	//w_ball = false;
	pos_ = weaponBall_->m_vPos;
}

//
//	@brief	��ѓ���f�X�g���N�^
WeaponBall::~WeaponBall()
{
	delete weaponBall_;
	weaponBall_ = nullptr;
	delete col_;
	col_ = nullptr;
	delete creator_;
	creator_ = nullptr;
}

//
//	@brief	�ǂݍ���
void WeaponBall::Init(char* name)
{
	weaponBall_ = creator_->LoadStage(name);
	/*char FileName[80] = "./Model/XFiles/Player/";
	strcat(FileName, name);
	if (FAILED(weaponBall_->LoadXMesh(FileName)))
	{
		return;
	}*/
}

//
//	@brief			�����Z�b�g
//	@param (dir)	�����x�N�g��
void WeaponBall::SetDir(D3DXVECTOR3 dir)
{
	dir_ = dir;
}

//
//	@brief			�T�C�Y�Z�b�g
//	@param (scale) �ύX����T�C�Y
void WeaponBall::SetScale(float scale)
{
	weaponBall_->m_fScale = scale;
}

//
// @brief	�����ʒu
void WeaponBall::SetStartPos(D3DXVECTOR3 pos)
{
	startPos_ = pos;
	weaponBall_->m_vPos = pos;
	spaceNo_ = col_->SetSpaceNo(startPos_, 2);

	//Effect::getInstance().Update("beam2", startPos_);
	//w_ball = true;
	//Effect::getInstance().Effect_Play("magicball", weaponBall_->m_vPos);
	//Effect::getInstance().SetScale("magicball", 0.2f);
}
//
//	@brief	�U���̓Z�b�g
void WeaponBall::SetAttack(unsigned int atk)
{
	atk_ = atk;
}

//
//	@brief			��ѓ���̈ړ��X�V
//	@param (dist)	�ړ��I������
void WeaponBall::Move_Weapon(float speed)
{
	//int ownNo = col_->SetSpaceNo(weaponBall_->m_vPos, 1);
	//if (col_->CharaNear(startPos_, weaponBall_->m_vPos, dist))
	//{
	float fDistance = 0;
	D3DXVECTOR3 vNormal;
	if (col_->RayIntersect(weaponBall_->m_vPos, dir_, Stage::GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
	{
		delFlg_ = true;
	}
	weaponBall_->m_vPos += D3DXVECTOR3(dir_.x*speed, 0, dir_.z*speed);
	//}
	//else
	//{
		//delFlg_ = true;
	//}

	spaceNo_ = col_->SetSpaceNo(weaponBall_->m_vPos, 2);

	Hit();
}

//
//	@brief	��莞�Ԍ�ɏ�����
void WeaponBall::Time_Del_Weapon(int frame)
{
	if (++delCount_ >= frame)
	{
		Hit();
		delFlg_ = true;
		effectflg_ = true;
		delCount_ = 0;
		//Effect::getInstance().Effect_Stop("magicball");
		//Effect::getInstance().Effect_Play("explosion", weaponBall_->m_vPos);
		//Effect::getInstance().SetScale("explosion", 0.8f);
	}
}

////
////	@brief			��e����\���̂���L�����N�^�[���X�g
////	@param (chara)	�_���[�W��H�炤�L����
//void WeaponBall::SetDamageList(std::vector<CharactorManager*> chara, CharaType cType,int no)
//{
//	for (auto c : chara)
//	{
//		if (c->GetCharaType() == Enemy)
//		{			
//			if (col_->CheckSpaceNo(spaceNo_, c->GetSpaceNo(), no, 2))
//			{
//				damageList_.push_back(c);
//			}
//		}
//	}
//}
//
////
////	@brief	��e����L�����X�V
////	@param (chara)	��e����L����
//void WeaponBall::SetDamageChara(CharactorManager* chara)
//{
//	damageList_.push_back(chara);
//}

//
//	@brief �e�������邩�ǂ���
bool WeaponBall::GetDelFlg()const
{
	return delFlg_;
}

//
//	@brief	���W�擾
D3DXVECTOR3 WeaponBall::GetPosition()const
{
	return weaponBall_->m_vPos;
}

//
//	@brief	�X�P�[���擾
float WeaponBall::GetScale()const
{
	return weaponBall_->m_fScale;
}

//
//	@brief	�U���q�b�g
void WeaponBall::Hit()
{
	//std::vector<CharactorManager*> hitList;
	//if (!damageList_.empty())
	//{
	for (auto c : CharactorManager::allCharaList_)
	{
		if (c->GetCharaType() != user_ && col_->CheckSpaceNo(spaceNo_, c->GetSpaceNo(), 1, 2))
		{
			damageList_.push_back(c);
		}

	}

	beforeDamageCharaList_.clear();
	if (!damageList_.empty())
	{
		for (auto d : damageList_)
		{
			if (!d->GetDamageFlg() && col_->CharaNear(weaponBall_->m_vPos, d->m_Pos, dist_))
			{
				d->SetKnockBack(weaponBall_->m_vPos, kDist_, kSpeed_, user_);
				if (hitDel_)
				{
					delFlg_ = true;
				}

				if (d->GetCharaType() == damageChara_)
				{
					d->DamageCalc(atk_);
					beforeDamageCharaList_.push_back(d);
					//�G�Ƀ_���[�W������������SE
					Sound::getInstance().SE_play(hitSoundName_);
				}
			}
		}
		damageList_.clear();
	}

}

//
//	@brief				�m�b�N�o�b�N�ݒ�
//	@param (dist)		�U���͈̔�
//	@param (kDist)		�m�b�N�o�b�N���鋗��
//	@param (kSpeed)		�m�b�N�o�b�N�X�s�[�h
//	@param (userChara)	�U���̎g�p��
//	@param (damageChara)�U����������L�����N�^�[�^�C�v
void WeaponBall::SetKnockBack(float dist, float kDist, float kSpeed, CharaType userChara, CharaType charatype)
{
	dist_ = dist;
	kDist_ = kDist;
	kSpeed_ = kSpeed;
	user_ = userChara;
	damageChara_ = charatype;
	beforeDamageCharaList_.clear();
}

//
//	@brief	�q�b�g�T�E���h�ݒ�
void WeaponBall::SetHitSound(std::string name)
{
	hitSoundName_ = name;
}

//
//	@brief	��������������邩�ǂ����t���O�ݒ�
void WeaponBall::SetHitDelFlg(bool flg)
{
	hitDel_ = flg;
}

////
////	@brief	�U���̓�����͈͎擾
//float WeaponBall::GetHitDist()const
//{
//	return dist_;
//}
//
////
////	@brief	�m�b�N�o�b�N���鋗���擾
//float WeaponBall::GetKnockBackDist()const
//{
//	return kDist_;
//}

//
//	@brief	�`��
void WeaponBall::Render(D3DXVECTOR3 pos)
{
	weaponBall_->Render(pos, D3DXVECTOR3(0, 0, 0), weaponBall_->m_fScale);

	//if (effectflg_)
	//{
	//	Effect::getInstance().Update("explosion", weaponBall_->m_vPos);
	//	effectflg_ = false;
	//}

}