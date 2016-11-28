#include "./Witch.h"


Witch::Witch(CharaType charaType) :JobManager(charaType)
{
	charaType_ = charaType;
	magicFlg_ = false;
	atkNo_ = noAtk;
	attackCount_ = 0;
	magic_ = new WeaponBall;
}

Witch::~Witch()
{
	delete magic_;
	magic_ = nullptr;
}

//
//	@brief						X�t�@�C���ǂݍ���
//	@param (m_hWnd)				�E�B���h�E�n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
//	@param (fileName)			�ǂݍ��ރL������
const char* Witch::CharaInit(const char* fileName)
{
	magic_->Init("magicball.x");

	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Player/");
	strcat_s(FileName, sizeof(FileName), fileName);
	return FileName;
	//CreateFromX(FileName);
	//m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	//ownWright_ = 0.001f;
}

//
//	@brief	�U��
void Witch::Attack()
{
	if (atkNo_ == noAtk)
	{
		moveAbleFlg_ = true;
	}
	else
	{
		moveAbleFlg_ = false;
	}

	//atkNo_ = noAtk;
	if (magicFlg_ == false && GamePad::checkInput(charaType_, GamePad::InputName::A)
		/*|| GetKeyState('1') & 0x80*/)
	{
		++attackCount_;
		atkNo_ = waitAtk;
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

		//hit = false;
	}
	//unsigned int inputTime = playerParam_.chargeTime_;

	unsigned int inputTime = FPS*param_->chargeTime_;

	if (0 < attackCount_ && attackCount_ <= inputTime)
	{
		atkNo_ = normalAtk;
	}
	else if (inputTime < attackCount_)
	{
		atkNo_ = charge;
		if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("charge")->id_)
		{
			motionChange_ = false;
			motionNo_ = motion_->GetMotion("charge")->id_;
			m_pD3dxMesh->ChangeAnimSet(motionNo_);
			//timeEnd_ = motion_->GetMotion("charge")->frame_;
			motionSpeed_ = 1 / (float)timeEnd_;
		}
	}

	if (atkNo_ == specialAtk)
	{
		Special_Attack();
	}

	if (magicFlg_ == true && !magicBall_.empty())
	{
		int count = 0;
		float kDist = param_->weaponDelDist_;
		float kSpeed = param_->knockbackSpeed_;
		for (size_t i = 0; i < magicBall_.size(); i++)
		{
			magicBall_[i]->Move_Weapon(kDist,kSpeed);
			if (magicBall_[i]->GetDelFlg())
			{
				magicBall_.erase(magicBall_.begin() + count);
				/*atkNo_ = noAtk;*/
				--count;
			}
			++count;
		}
		if (magicBall_.empty())
		{
			magicBall_.clear();
			magicFlg_ = false;
		}
	}
}

//
//	@brief	�ʏ�U��
void Witch::Normal_Attack()
{
	//float dist = param_->attackReach_;
	float kRange = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	magicBallCount_ = param_->chainWeapon_;
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack")->id_)
	{
		motionChange_ = false;
		motionNo_ = motion_->GetMotion("attack")->id_;
		m_pD3dxMesh->ChangeAnimSet(motionNo_);
		timeEnd_ = motion_->GetMotion("attack")->frame_;
		motionSpeed_ = 1 / (float)timeEnd_;
		motionCount_ = 0;
	}

	if (++motionCount_%timeEnd_ == 0)
	{
		atkNo_ = noAtk;
		motionChange_ = true;
	}

	if(!magicFlg_)
	{
		WeaponBall* magic= new WeaponBall();

		D3DXVECTOR3 vec(sinf(m_Yaw)*-0.1, 0, cosf(m_Yaw)*-0.1);
		magic->SetDir(vec);
		magic->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y+1, m_Pos.z));
		magic->SetDamageList(allCharaList_, charaType_);
		magic->SetKnockBack(kRange, kDist, kSpeed);
		magic->SetAttack(param_->normalAtk_);
		magicBall_.push_back(magic);
		magicFlg_ = true;
	}
}

//
//	@brief	����U��
void Witch::Special_Attack()
{
	float kRange = param_->weaponHitReach_;
	float kDist = param_->knockbackDist_;
	float kSpeed = param_->knockbackSpeed_;
	magicBallCount_ = param_->spChainWeapon_;
	if (/*motionChange_ == true && */motionNo_ != motion_->GetMotion("attack")->id_)
	{
		motionChange_ = false;
		motionNo_ = motion_->GetMotion("attack")->id_;
		m_pD3dxMesh->ChangeAnimSet(motionNo_);
		timeEnd_ = motion_->GetMotion("attack")->frame_;
		motionSpeed_ = 1 / (float)timeEnd_;
		motionCount_ = 0;
	}

	if (++motionCount_%timeEnd_ == 0)
	{
		atkNo_ = noAtk;
		motionChange_ = true;
	}

	if(!magicFlg_)
	{
		float angle = D3DXToDegree(m_Yaw);
		for (int i = 0; i < magicBallCount_; i++)
		{
			WeaponBall* magic = new WeaponBall;
			int degree = 90 / (magicBallCount_ / 2 + 1);
			float temp = angle - 90 + degree + degree*i;
			temp = D3DXToRadian(temp);
			D3DXVECTOR3 vec(sinf(temp)*-0.1, 0, cosf(temp)*-0.1);
			magic->SetDir(vec);
			magic->SetScale(0.5);
			magic->SetStartPos(D3DXVECTOR3(m_Pos.x, m_Pos.y + 1, m_Pos.z));
			magic->SetDamageList(allCharaList_, charaType_);
			magic->SetKnockBack(kRange, kDist,kSpeed);
			magic->SetAttack(param_->specialAtk_);
			magicBall_.push_back(magic);
		}
		magicFlg_ = true;
		//atkNo_ = noAtk;
	}
}

//
//	@brief	�`��
void Witch::CharaRender()
{
	Render(m_Pos);
	if (!magicBall_.empty())
	{
		for (auto m:magicBall_)
		{
			magic_->Render(m->GetPosition());
		}
	}
}