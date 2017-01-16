//
//	@file	EnemyManager.cpp
//	@brief	�G�l�~�[�Ǘ��N���X
//	@date	2016/11/13
//	@author�@�g�z��R
//	@author	�m�ȍ��c

#include "EnemyManager.h"

std::vector<D3DXVECTOR3> EnemyManager::busStop_;
std::vector<int> EnemyManager::busStopSpaceNo_;

EnemyManager::EnemyManager()
{
	charaType_ = Enemy;
	m_Pos = { 0,0,0 };
	aliveFlg_ = true;
	moveAbleFlg_ = true;
	//opponentWeight_ = 1;
	//targetPos_ = D3DXVECTOR3(0, 0, 0);
	collision_ = new Collision;
	param_ = new EnemyParam;
}

EnemyManager::~EnemyManager()
{
	delete collision_;
	collision_ = nullptr;
	//delete motion_;
	//motion_ = nullptr;
}


//
//	@brief	�p�����[�^�Z�b�g
void EnemyManager::SetParameter(char* name)
{
	ParameterRead* parameter = new ParameterRead;
	//parameter->SetJobParameter();
	EnemyParameter* enemy = parameter->GetEnemyParamList(name);


	memset(param_->name_, 0, sizeof(param_->name_));
	memcpy(param_->name_, enemy->GetName(), sizeof(param_->name_));

	param_->hp_ = enemy->GetHP();
	param_->def_ = enemy->GetDefence();
	param_->moveSpeed_ = enemy->GetMoveSpeed();
	param_->weight_ = enemy->GetWeight();
	param_->atk_ = enemy->GetAtk();
	param_->attackReach_ = enemy->GetAttackReach();
	param_->scale_ = enemy->GetScale();

	m_Scale = D3DXVECTOR3(param_->scale_, param_->scale_, param_->scale_);
	ownWeight_ = param_->weight_;
	hp_ = param_->hp_;

}

//
//	@brief	���f���̐ݒ�
void EnemyManager::SetModel(CD3DXSKINMESH* mesh)
{
	mesh_ = mesh;
}

//
//	@brief	�o�X��Z�b�g
void EnemyManager::SetBusStop(std::vector<D3DXVECTOR3> pos)
{
	busStop_ = pos;
	Collision* col = new Collision;
	for (auto p : pos)
	{
		int no = col->SetSpaceNo(p);
		busStopSpaceNo_.push_back(no);
	}
	//delete col;
	//col = nullptr;
}

//
//	@brief�@			�^�[�Q�b�g�ݒ�
//	@param (chara)		�^�[�Q�b�g�ɂ���L����
void EnemyManager::SetTarget(CharactorManager* chara)
{
	targetChar_ = chara;
	
}

//
//	@brief	�^�[�Q�b�g���W�Z�b�g
void EnemyManager::SetTargetPos(D3DXVECTOR3 pos)
{
	targetPos_ = pos;

	for (auto no : busStopSpaceNo_)
	{
		if (collision_->CheckSpaceNo(spaceNo_, no))
		{
			return;
		}
	}

	float dist = pow(m_Pos.x - targetPos_.x, 2) + pow(m_Pos.z - targetPos_.z, 2);
	float degree = D3DXToDegree(m_Yaw);
	D3DXVECTOR3 vec = targetPos_ - m_Pos;
	float angle = (atan2(vec.z, vec.x)*-1) - (D3DX_PI / 2.0f);
	angle = D3DXToDegree(angle);

	for (auto p : busStop_)
	{
		float temp = pow(m_Pos.x - p.x, 2) + pow(m_Pos.z - p.z, 2);
		D3DXVECTOR3 tempVec = p - m_Pos;
		float tempAngle = (atan2(tempVec.z, tempVec.x)*-1) - (D3DX_PI / 2.0f);
		tempAngle = D3DXToDegree(tempAngle);
		if (temp < dist && fabsf(degree - angle) <= 90)
		{
			targetPos_ = p;
			dist = temp;
		}
	}

	
}

//
//	@brief�@					�^�[�Q�b�g�̍X�V
//	@param (chara)			�v���C���[
//	@param (princess)		�P
void EnemyManager::Target_Update(CharactorManager * chara, CharactorManager * princess)
{
	CharactorManager* temp = targetChar_;
	//float dist = 5;

	if (perpetrator_ == chara->GetCharaType())
	{
		temp = chara;
	}

	////���݂̃^�[�Q�b�g���P
	//if (targetChar_->GetCharaType() == princess->GetCharaType())
	//{
	//	if (collision_->CharaNear(m_Pos, chara->m_Pos, dist))
	//	{
	//		temp = chara;
	//	}
	//}

	//�^�[�Q�b�g������ł���
	if (!targetChar_->GetAliveFlg())
	{
		temp = princess;
	}

	//�^�[�Q�b�g�̍X�V
	SetTarget(temp);
	SetTargetPos(temp->m_Pos);
}

//
//	@brief�@			�^�[�Q�b�g�|�W�V�����̍X�V
//	@param (position)	���W
void EnemyManager::SetTargetChar(CharactorManager* checkChar, CharactorManager* princess)
{
	////���݂̃^�[�Q�b�g�ƃ`�F�b�N����v���C���[����v���邩
	//if (targetChar_->GetCharaType() == checkChar->GetCharaType())
	//{
	//	//�`�F�b�N����(���݃^�[�Q�b�g�̃v���C���[�j���������Ă��邩
	//	if (checkChar->GetAliveFlg())
	//	{
	//		//�^�[�Q�b�g�X�V
	//		targetChar_ = checkChar;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//	else
	//	{
	//		//�^�[�Q�b�g��P�ɕύX
	//		targetChar_ = princess;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//}
	//else if (targetChar_->GetCharaType() == princess->GetCharaType()/* || targetChar_ == nullptr*/)       //���݂̃^�[�Q�b�g���P
	//{
	//	//�߂��ɐ����Ă���v���C���[�����邩�ǂ���(�`�F�b�N����v���C���[�������Ă��� ���� ���������ȓ�)
	//	if (checkChar->GetAliveFlg() && collision_->CharaNear(m_Pos, checkChar->m_Pos, 50.0))
	//	{
	//		//�^�[�Q�b�g���v���C���[�ɕύX
	//		targetChar_ = checkChar;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//	else         //�߂��ɐ����Ă���v���C���[�����Ȃ�
	//	{
	//		//�^�[�Q�b�g�X�V
	//		targetChar_ = princess;
	//		targetPos_ = targetChar_->m_Pos;
	//	}
	//}

	////if (!targetChar_->GetAliveFlg())
	////{
	////	targetChar_ = princess;
	////	targetPos_ = targetChar_->m_Pos;
	////}
}

//
//	@brief			�ړ�����
//	@param (speed)	�ړ����x
void EnemyManager::Move(float speed)
{
	if (knockBackFlg_)
	{
		KnockBack(knockBackPos_, knockBackDis_, knockBackSpeed_);
		return;
	}

	D3DXVECTOR3 E_Lock;
	E_Lock.x = targetPos_.x - m_Pos.x;
	E_Lock.z = targetPos_.z - m_Pos.z;

	D3DXVec3Normalize(&E_Lock, &E_Lock);

	//��]����
	Rotation(E_Lock);

	//�����Ă���p�x����P�ʃx�N�g�����擾
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-1, 0, cosf(m_Yaw)*-1);
	//D3DXVECTOR3 vec = E_Lock;
	float sp = speed;
	//opponentWeight_ = 1;
	m_Dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);

	if (motionNo_ != motion_->GetMotion("walk")->id_)
	{
		ChangeMotion(motion_, "walk");
		//motionNo_ = motion_->GetMotion("walk")->id_;
		//mesh_->m_pD3dxMesh->ChangeAnimSet(motionNo_);
		//motionSpeed_ = 1 / (float)motion_->GetMotion("walk")->frame_;
	}

}

//
//	@brief	�_���[�W�v�Z
void EnemyManager::DamageCalc(unsigned int atk)
{

	float damage = atk / (1 + ((float)param_->def_ / 100));
	hp_ -= damage;

	if (hp_ <= 0 || param_->hp_ < hp_)
	{
		hp_ = 0;
		aliveFlg_ = false;
	}
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
	float atkableDist = 2;//param_->attackReach_;
	int time = 3;

	if (collision_->CharaNear(m_Pos, targetPos_, atkableDist))
	{
		if (++atkWaitTime_ % (FPS*time) == 0)
		{
			moveAbleFlg_ = false;
			NormalAttack();
		}
		else
		{
			moveAbleFlg_ = true;
		}
	}
	else
	{
		moveAbleFlg_ = true;
		atkWaitTime_ = 0;
	}
}
