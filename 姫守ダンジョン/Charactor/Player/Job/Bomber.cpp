#include "./Bomber.h"

Bomber::Bomber(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	bombFlg_ = false;
	bomb_.clear();
	bombScale_ = 1;
	bombCount_ = 1;
	invincibleFlg_ = false;
}

Bomber::~Bomber()
{

}

//
//	@brief	�U��
void Bomber::Attack()
{
	if (GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
	}
	else if (atkNo_ == normalAtk)
	{
		attackCount_ = 0;
		Normal_Attack();
	}
	else if (atkNo_ == charge)
	{
		attackCount_ = 0;
		atkNo_ = specialAtk;
		invincibleFlg_ = true;
		//hit = false;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = param_->chargeTime_;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
	}

	if (invincibleFlg_)
	{
		Special_Attack();
	}

	if (!bomb_.empty())
	{
		bombFlg_ = true;
		//static int count = 0;
		//int count = 0;
		float delTime = FPS*param_->weaponDelTime_;
		for (auto b : bomb_)
		{
			b->Time_Del_Weapon(delTime);
		}
		if (/*b != nullptr &&*/ bomb_[0]->GetDelFlg())
		{
			bomb_.erase(bomb_.begin());

			//delete b;
			//b = nullptr;
			//++count;
			//--count;
		}
		//++count;
		if (bomb_.empty())
		{
			bomb_.clear();
			bombFlg_ = false;
			//count = 0;
		}

		/*if (count == bombCount_)
		{
		bomb_.clear();
		bombFlg_ = false;
		count = 0;
		}*/
	}
}

//
//	@brief	�ʏ�U��
void Bomber::Normal_Attack()
{
	size_t size = param_->chainWeapon_;
	float range = param_->attackRange_;
	float dist = param_->attackReach_;
	float kSpeed = param_->knockbackSpeed_;

	if (bomb_.empty() || bomb_.size() < size)
	{
		WeaponBall* bomb = new WeaponBall(m_hWnd, m_pDevice, m_pDeviceContext, m_Pos);
		bomb->SetDamageList(allCharaList_, charaType_);
		bomb->SetKnockBack(range, dist, kSpeed);
		bomb_.push_back(bomb);
	}
	atkNo_ = noAtk;
}

//
//	@brief	����U��
void Bomber::Special_Attack()
{
	int invincibleTime = param_->specialAttackTime_;
	if (++timeCount_ % (FPS * invincibleTime) == 0)
	{
		invincibleFlg_ = false;
		timeCount_ = 0;
	}
	atkNo_ = noAtk;
}

//
//	@brief	���e�m�p�ړ�����
void Bomber::Move_Update()
{
	float kSpeed = param_->knockbackSpeed_;
	if (aliveFlg_ == true)
	{
		if (knockBackFlg_ == false)
		{
			m_Pos += m_Dir;
		}
		else if (knockBackFlg_ == true && invincibleFlg_ == false)
		{
			KnockBack(knockBackPos_, knockBackDis_, kSpeed);
		}
	}
}


//
//	@brief			�_���[�W�v�Z
//	@param (atk)	�U���҂̍U����
void Bomber::DamageCalc(unsigned int atk)
{
	float damage = 0;
	if (invincibleFlg_ == false)
	{
		damage = atk / (1 + ((float)param_->def_ / 100));
	}

	hp_ -= damage;
	if (hp_ <= 0)
	{
		hp_ = 0;
		aliveFlg_ = false;
	}

}

//
//	@brief	�`��
void Bomber::CharaRender(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	m_View = mView;
	m_Proj = mProj;
	Render();
	if (!bomb_.empty())
	{
		for (auto b : bomb_)
		{
			if (b != nullptr)
			{
				b->Render(mView, mProj);
			}
		}
	}
}