#include "./WeaponBall.h"


//
//	@brief	��ѓ���R���X�g���N�^
WeaponBall::WeaponBall(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, D3DXVECTOR3 pos)
	:delCount_(0)
{
	weaponBall_ = new STATICMESH::CD3DXMESH;
	char FileName[80] = "./Model/XFiles/Player/scale1.x";
	if (FAILED(weaponBall_->Init(m_hWnd, m_pDevice, m_pDeviceContext, FileName)))
	{
		return;
	}
	weaponBall_->m_vPos = pos;
	weaponBall_->m_fScale = 0.5;
	startPos_ = pos;
	delFlg_ = false;
	col_ = new Collision;
}

//
//	@brief	��ѓ���f�X�g���N�^
WeaponBall::~WeaponBall()
{
	delete weaponBall_;
	weaponBall_ = nullptr;
	delete col_;
	col_ = nullptr;
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
	weaponBall_->m_fScale += scale;
}

//
//	@brief			��ѓ���̈ړ��X�V
//	@param (dist)	�ړ��I������
void WeaponBall::Move_Weapon(float dist)
{
	float speed = 3;
	if (col_->CharaNear(startPos_, weaponBall_->m_vPos, dist))
	{
		weaponBall_->m_vPos += D3DXVECTOR3(dir_.x*speed, 0, dir_.z*speed);
	}
	else
	{
		delFlg_ = true;
	}
	
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
		delCount_ = 0;
	}
}

//
//	@brief			��e����\���̂���L�����N�^�[���X�g
//	@param (chara)	�_���[�W��H�炤�L����
void WeaponBall::SetDamageList(std::vector<CharactorManager*> chara, CharaType cType)
{
	for (auto c : chara)
	{
		if (c->GetCharaType() != cType)
		{
			if (col_->CharaNear(weaponBall_->m_vPos, c->m_Pos, range_))
			{
				damageList_.push_back(c);
			}
		}
	}
}

//
//	@brief	��e����L�����X�V
//	@param (chara)	��e����L����
void WeaponBall::SetDamageChara(CharactorManager* chara)
{
	damageList_.push_back(chara);
}

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
//	@brief	�U���q�b�g
void WeaponBall::Hit()
{
	if (!damageList_.empty())
	{
		for (auto c : damageList_)
		{
			if (col_->CharaNear(weaponBall_->m_vPos, c->m_Pos, range_))
			{
				c->SetKnockBack(weaponBall_->m_vPos, 10);
				delFlg_ = true;
			}
		}
	}
}

//
//	@brief			�U���͈͂̐ݒ�ƃm�b�N�o�b�N�����̐ݒ�
//	@param (range)	�U���͈̔�
//	@param (dist)	�m�b�N�o�b�N���鋗��
void WeaponBall::SetHitRangeKnockBackDist(float range, float dist)
{
	range_ = range;
	dist_ = dist;
}

//
//	@brief	�U���̓�����͈͎擾
float WeaponBall::GetHitRange()const
{
	return range_;
}

//
//	@brief	�m�b�N�o�b�N���鋗���擾
float WeaponBall::GetKnockBackDist()const
{
	return dist_;
}

//
//	@brief	�`��
void WeaponBall::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	weaponBall_->Render(mView, mProj, D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1));
}