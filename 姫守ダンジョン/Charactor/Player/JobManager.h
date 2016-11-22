//
//	@file	JobManager.h
//	@brief	�E�Ɩ��̏���
//	@date	2016/11/10
//	@outher	�m�ȍ��c

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"
#include "./../../Mesh/CD3DXMESH.h"
#include "./Job/WeaponBall.h"
#include "./../../Read/ParameterRead.h"


//	�p�����[�^
struct PlayerParameter
{
	char* name_;				//�E�Ɩ�
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//�ʏ�U����
	unsigned int specialAtk_;	//����U����
	unsigned int def_;			//�����
	unsigned int chargeTime_;	//�`���[�W�^�C��
	float specialAttackTime_;	//�ҋ@����
	float moveSpeed_;			//�ړ����x
	float specialMoveSpeed_;	//����ړ����x
	float weight_;				//�d��
	float attackReach_;			//�U�����[�`
	float attackRange_;			//�U���͈�
	float scale_;				//�X�P�[��
};

//	�E�ƊǗ��N���X
class JobManager :public PlayerManager
{
protected:
	unsigned int timeCount_;	//�U������
	unsigned int timeEnd_;		//�U���I������
	int attackCount_;			//�U���{�^���J�E���g
	
	PlayerParameter* param_;

	//void Motion_Update();

	Collision* col_;

public:
	JobManager(CharaType charaType);
	virtual ~JobManager();
	virtual void CharaUpdate();
	//template<class> p;
	void SetParameter(JobParameter* param);
	//PlayerParameter GetParam()const;
	bool hit;//�f�o�b�O�p

	int GetAtkCnt() { return attackCount_; };

	//�f�o�b�N�p
	PlayerParameter* GetParam()const { return param_; };
};

