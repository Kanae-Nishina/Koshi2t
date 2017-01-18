//
//	@file	Princess.h
//	@brief	�P�N���X
//	@date	2016/12/01
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#include "./Princess.h"

//
//	@brief	�R���X�g���N�^
Princess::Princess()
{
	sealFlg_ = false;
	resFlg_ = false;
	sealSpawn_ = nullptr;
	charaType_ = PrincessT;
}

//
//	@brief	�f�X�g���N�^
Princess::~Princess()
{
}

void Princess::SetParameter(char* name)
{
	ParameterRead* parameter = new ParameterRead;
	parameter->SetPricessParameter();
}

//
//	@brief	���Z�b�g
void Princess::Reset()
{
	motionCount_ = 0;
	motionChange_ = true;
	opponentWeight_ = 1;
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	sealFlg_ = false;
	resFlg_ = false;
	aroundCharaList_.clear();
	allCharaList_.clear();
	deadCharaList_.clear();
	m_Pos = D3DXVECTOR3(0, 0, -12);
	destination_ = m_Pos;
	sealSpawn_ = nullptr;
	spawnPosList_.clear();
}

//
//	@brief	�ړ�
void Princess::Move(float speed)
{
	if (knockBackFlg_ == true)
	{
		KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
		return;
	}

	float dist = 1;
	//int spNo = collision_->SetSpaceNo(destination_);
	//if (!collision_->CheckSpaceNo(spaceNo_, spNo))
	if(!collision_->CharaNear(m_Pos,destination_,dist))
	{
		//�����x�N�g��
		D3DXVECTOR3 move = { 0,0,0 };
		move.x = destination_.x - m_Pos.x;
		move.z = destination_.z - m_Pos.z;
		D3DXVec3Normalize(&move, &move);

		//��]
		Rotation(move);

		//�����Ă����������p�x���擾
		D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-1, 0, cosf(m_Yaw)*-1);

		float sp = speed;
		m_Dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);

		if (motionChange_==true && motionNo_ != motion_->GetMotion("walk")->id_)
		{
			motionNo_ = motion_->GetMotion("walk")->id_;
			mesh_->m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("walk")->id_);
			motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
		}
	}
	else
	{
		m_Dir = D3DXVECTOR3(0, 0, 0);

		if (motionChange_ == true && motionNo_ != motion_->GetMotion("wait")->id_)
		{
			motionNo_ = motion_->GetMotion("wait")->id_;
			mesh_->m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("wait")->id_);
			motionSpeed_ = 1 / (float)motion_->GetMotion("wait")->frame_;
		}
	}
}


//
//	@brief	�_���[�W�v�Z
//	@note	�P�̏ꍇ�͎��S
void Princess::DamageCalc(unsigned int atk)
{
	aliveFlg_ = false;
	if (motionChange_ == true && motionNo_ != motion_->GetMotion("dead1")->id_ && motionNo_ != motion_->GetMotion("dead2")->id_)
	{
		moveAbleFlg_ = false;
		ChangeMotion(motion_, "dead1");
		motionCount_ = 0;
	}
	if (++motionCount_>motionFrame_ && motionNo_ == motion_->GetMotion("dead1")->id_)
	{
		ChangeMotion(motion_, "dead2");
		motionCount_ = 0;
		motionChange_ = true;
	}
}

//
//	@brief	�ړI�n�Z�b�g
void Princess::SetDestination(D3DXVECTOR3 pos)
{
	destination_ = pos;
}


//
//	@brief	���󂷂�X�|�[���Q�[�g�̎擾
void Princess::SetSpawn(std::vector<Spawn*> spawn)
{
	for (auto s : spawn)
	{
		spawnPosList_.push_back(s);
	}
}

//
//	@brief	����
void Princess::Seal()
{
	float dist = 5;
	if (!spawnPosList_.empty())
	{
		for (auto spawn : spawnPosList_)
		{
			if (collision_->CharaNear(m_Pos, spawn->GetPos(), dist))
			{
				sealFlg_ = true;
				sealSpawn_ = spawn;
			}
		}
	}
}

//
//	@brief	���󂷂�X�|�[���Q�[�g��Ԃ�
Spawn* Princess::SealSpawn()
{

	if (sealFlg_ == true)
	{
		if (motionNo_ != motion_->GetMotion("prayer")->id_)
		{
			motionChange_ = false;
			//m_pD3dxMesh->ChangeAnimSet(motion_->GetMotion("prayer")->id_);
			//motionSpeed_ = 1 / (float)motion_->GetMotion("prayer")->frame_;
			ChangeMotion(motion_, "prayer");
		}

		if (++motionCount_>motion_->GetMotion("prayer")->frame_)
		{
			sealFlg_ = false;
			motionCount_ = 0;
			motionChange_ = true;
			//ChangeMotion(motion_, "wait");
			auto el = std::find(spawnPosList_.begin(), spawnPosList_.end(), sealSpawn_);
			spawnPosList_.erase(el);
			return sealSpawn_;
		}
	}
	return nullptr;
}

//
//	@brief	�h��
void Princess::Resuscitation()
{
	//float resDist = 100;
	std::list<CharactorManager*> resList;
	if (!deadCharaList_.empty())
	{
		for (auto c : deadCharaList_)
		{
			//if (collision_->CharaNear(m_Pos, c->m_Pos, resDist))
			if (collision_->CheckSpaceNo(spaceNo_, c->GetSpaceNo()))
			{

				//if(motionNo_!=motion_->GetMotion("prayer"))
				c->SetRevivalFlg();
				resList.push_back(c);
			}
		}
	}



	if (!resList.empty())
	{
		for (auto c : resList)
		{
			auto res = std::find(deadCharaList_.begin(), deadCharaList_.end(), c);
			deadCharaList_.erase(res);
		}
		resList.clear();
	}
}

//
//	@breif	���S�L�����Z�b�g
void Princess::SetDeadCharaList(PlayerManager* chara)
{
	deadCharaList_.push_back(chara);
}

//
//	@brief	�X�V
void Princess::CharaUpdate()
{
	//��Ԕԍ��̍X�V
	spaceNo_ = collision_->SetSpaceNo(m_Pos);

	//�ړ�
	float speed = 0.05;
	MoveCharaHit();
	Move(speed);

	//�h��
	Resuscitation();

	//����
	Seal();

	//���[�V�����X�s�[�h
	mesh_->m_pD3dxMesh->m_pAnimController->AdvanceTime(motionSpeed_, NULL);

}