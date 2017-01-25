//
//	@file	Witch.cpp
//	@brief	�����m�N���X
//	@date	2016/11/21
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#include "./Witch.h"


Witch::Witch(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	magicFlg_ = false;
	atkNo_ = noAtk;
	attackCount_ = 0;
	magic_ = new CD3DXMESH;
	magicSpeed_ = 3.0f;
	magic_ = creator_->LoadStage("���@��");

	//UI
	jobMarkUI_ = new TD_Graphics;
	jobUIPos_ = D3DXVECTOR2(30 + charaType*UI_INTERVAL + UI_SPACE, 860);
	D3DXVECTOR2 scale(105, 100);
	jobMarkUI_->Init(L"./UI/UI_Tex/mage.png", jobUIPos_, scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	//Witch_UI["WITCH_UI"] = new TD_Graphics;
}

Witch::~Witch()
{
	delete magic_;
	magic_ = nullptr;
	delete jobMarkUI_;
	jobMarkUI_ = nullptr;
	//delete Witch_UI["WITCH_UI"];
	//magic_ = nullptr;
}



//
//	@brief	���Z�b�g
void Witch::Reset()
{
	hp_ = param_->hp_;
	motionCount_ = 0;
	motionChange_ = true;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	aroundCharaList_.clear();
	allCharaList_.clear();
	atkNo_ = noAtk;
	revivalFlg_ = false;
	callTiming_ = 0;
	attackCount_ = 0;
	magicFlg_ = false;
	magicBall_.clear();

	m_Pos = D3DXVECTOR3(-2.25 + charaType_*1.5, 0, -10);
}


//
//	@brief	�U��
void Witch::Attack()
{
	//atkNo_ = noAtk;
	if (/*magicFlg_ == false && */GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		//atkNo_ = waitAtk;
		moveAbleFlg_ = false;
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
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;
	static bool chargeMotionFlg = false;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
		moveAbleFlg_ = false;
		if (!chargeMotionFlg && motionNo_ != motion_->GetMotion("charge1")->id_)
		{
			motionChange_ = false;
			chargeMotionFlg = true;
			//motionNo_ = motion_->GetMotion("charge")->id_;
			//m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//timeEnd_ = motion_->GetMotion("attack")->frame_;
			//motionSpeed_ = 1 / (float)timeEnd_;
			//motionCount_ = 0;
			ChangeMotion(motion_, "charge1");
		}
		else if (++motionCount_ > motionFrame_&& chargeMotionFlg &&  motionNo_ != motion_->GetMotion("charge2")->id_)
		{
			ChangeMotion(motion_, "charge2");
		}
	}

	if (atkNo_ == specialAtk)
	{
		chargeMotionFlg = false;
		Special_Attack();
	}


}

//
//	@brief	�ʏ�U��
void Witch::Normal_Attack()
{
	//float dist = param_->attackReach_;
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack1");
	}

	if (++motionCount_ > motionFrame_)
	{
		Sound::getInstance().SE_play("M_NORMALATK");
		atkNo_ = noAtk;
		motionChange_ = true;
		moveAbleFlg_ = true;
		InstanceMagicBall(param_->attackRange_, param_->normalAtk_, true);
		Effect::getInstance().Effect_Play("magicball", m_Pos);
		Effect::getInstance().SetScale("magicball", 0.2);
	}


}

//
//	@brief	����U��
void Witch::Special_Attack()
{
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack1")->id_)
	{
		motionChange_ = false;
		//motionNo_ = motion_->GetMotion("attack")->id_;
		//m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//timeEnd_ = motion_->GetMotion("attack")->frame_;
		//motionSpeed_ = 1 / (float)timeEnd_;
		//motionCount_ = 0;
		ChangeMotion(motion_, "attack1");
	}

	if (++motionCount_ > motionFrame_)
	{
		/*	Sound::getInstance().SE_play("M_SPECIAL");

			Effect::getInstance().Effect_Play("magicball", D3DXVECTOR3(m_Pos.x, m_Pos.y + 1.0, m_Pos.z));
			float yaw = D3DXToDegree(m_Yaw) + 180;
			Effect::getInstance().SetRotation("magicball", D3DXVECTOR3(0, D3DXToRadian(yaw), 0));*/
			//Effect::getInstance().SetScale("magicball", 1.2);

		Sound::getInstance().SE_play("M_SPECIAL");
		atkNo_ = noAtk;
		motionChange_ = true;
		moveAbleFlg_ = true;
		InstanceMagicBall(param_->specialAtkRange_, param_->specialAtk_,false);
		Effect::getInstance().Effect_Play("magicball", m_Pos);
		Effect::getInstance().SetScale("magicball", 0.2);
		//RazorBeam();
	}


}

//
//	@brief	�}�W�b�N�{�[������
void Witch::InstanceMagicBall(float range, float atk, bool flg)
{
	//float kRange = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	if (!magicFlg_)
	{
		float angle = D3DXToDegree(m_Yaw);
		//for (int i = 0; i < magicBallCount_; i++)
		//{
		WeaponBall* magic = new WeaponBall;
		/*int degree = 90 / (magicBallCount_ / 2 + 1);
		float temp = angle - 90 + degree + degree*i;
		temp = D3DXToRadian(temp);*/
		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magic->SetDir(vec);
		magic->SetScale(0/*param_->weaponScale_*/);
		magic->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1, m_Pos.z));
		magic->SetDamageList(allCharaList_, charaType_, 1);
		magic->SetKnockBack(range, kDist, kSpeed, charaType_);
		magic->SetAttack(atk);
		magic->SetHitSound("M_DAMAGE_HIT");
		magic->SetHitDelFlg(flg);
		magicBall_.push_back(magic);
		//}
		magicFlg_ = true;
	}
}

//
//	@brief	�}�W�b�N�{�[���̍X�V
void Witch::WeaponUpdate()
{
	std::vector<WeaponBall*> dellist;

	if (magicFlg_ && !magicBall_.empty())
	{
		for (auto m : magicBall_)
		{
			m->Move_Weapon(magicSpeed_);
			m->SetDamageList(allCharaList_, charaType_, 1);
			Effect::getInstance().Update("magicball", m->GetPosition());
			if (m->GetDelFlg())
			{
				dellist.push_back(m);
			}
		}
	}
	else
	{
		magicBall_.clear();
		magicFlg_ = false;
	}

	if (!dellist.empty())
	{
		for (auto d : dellist)
		{
			auto e = std::find(magicBall_.begin(), magicBall_.end(), d);
			delete (*e);
			magicBall_.erase(e);
		}
		Effect::getInstance().Effect_Stop("magicball");
		//Effect::getInstance().Effect_Stop("beam2");
		dellist.empty();
	}

}

//
//	@brief	���[�U�[�r�[��
void Witch::RazorBeam()
{
	magicSpeed_ = 3.0f;
	float kRange = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	if (!magicFlg_)
	{
		WeaponBall* magic = new WeaponBall;
		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magic->SetDir(vec);
		magic->SetScale(0);
		magic->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y, m_Pos.z));
		magic->SetDamageList(allCharaList_, charaType_, 1);
		magic->SetKnockBack(kRange, kDist, kSpeed, charaType_);
		magic->SetAttack(param_->specialAtk_);
		magic->SetHitSound("M_DAMAGE_HIT");
		magic->SetHitDelFlg(false);
		magicBall_.push_back(magic);

		magicFlg_ = true;
	}
}

//
//	@brief	��_������SE�Đ�
void Witch::DamageSound()
{
	Sound::getInstance().SE_play("M_DAMAGE");
}

//
//	@brief	���S���Đ�
void Witch::DeadSound()
{
	Sound::getInstance().SE_play("M_DEAD");
}

//
//	@brief	�`��
void Witch::CharaRender()
{
	//D3DXVECTOR2 pos(0, 0);
	//D3DXVECTOR2 size(1, 1);
	//Witch_UI["WITCH_UI"]->Render(pos,size);

	//���f���`��
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);
	bool drawFlg = true;
	if (damageFlg_)
	{
		if (++damageCount_ % 5 == 0)
		{
			drawFlg = false;
		}
	}
	if (drawFlg)
	{
		float scale = 0.2f;
		mesh_->Render(m_Pos, m_Yaw, D3DXVECTOR3(scale, scale, scale));
	}
	//���@�`��
	if (!magicBall_.empty())
	{
		for (auto m : magicBall_)
		{
			magic_->Render(m->GetPosition(), D3DXVECTOR3(0, 0, 0), m->GetScale());
		}
	}

	//Effect::getInstance().Draw();

	//UI�`��
	UIRender();
}