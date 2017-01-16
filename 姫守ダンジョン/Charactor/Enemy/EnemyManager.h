//
//	@file	EnemyManager.h
//	@brief	�G�Ǘ��N���X
//	@date	2016/11/13
//	@author	�g�z��R
//	@author	�m�ȍ��c

#pragma once
#include "./../CharactorManager.h"
#include "./../../DebugDraw/D3D11_TEXT.h"
#include "./../../Read/ParameterRead.h"

//	�p�����[�^
struct EnemyParam
{
	char name_[30];				//�G�̖�
	unsigned int hp_;			//HP
	unsigned int atk_;			//�ʏ�U����
	unsigned int def_;			//�����
	unsigned int waitTime_;		//�ҋ@����
	float moveSpeed_;			//�ړ����x
	float attackReach_;			//�U������
	float weight_;				//�d��
	float scale_;				//�T�C�Y
};

class EnemyManager : public CharactorManager
{
private:
	D3DXVECTOR3 targetPos_;
	static std::vector<D3DXVECTOR3> busStop_;
	static std::vector<int> busStopSpaceNo_;

	enum TargetObject
	{
		princess = 0,
		player,
	};
	TargetObject targetObj_;


	void SetTargetPos(D3DXVECTOR3 pos);
protected:
	unsigned int atkWaitTime_;	//�U������Ԋu

	EnemyParam* param_;
	CharactorManager* targetChar_;
	D3DXVECTOR3 getpos_;
	virtual void Move(float speed);		//�ړ�����
	virtual void Attack();
	virtual void NormalAttack() = 0;
	virtual void Dead();				//���S
	virtual void DamageCalc(unsigned int atk);
	virtual void DamageSound() {};		//�_���[�W�T�E���h
	virtual void SetParameter(char* name);
public:
	EnemyManager();
	virtual ~EnemyManager();

	static void SetBusStop(std::vector<D3DXVECTOR3> pos);
	void SetTarget(CharactorManager* chara);
	void Target_Update(CharactorManager* chara, CharactorManager* princess);

	void SetTargetChar(CharactorManager* checkChar, CharactorManager* princess);	//�߂��ɂ��邩����
	void SetModel(CD3DXSKINMESH* mesh);
	D3DXVECTOR3 GetTargetPos() { return targetPos_; };	//�^�[�Q�b�g�|�W�V�����擾�f�o�b�N�p
	EnemyParam* GetParam() { return param_; };
	CharactorManager* GetTarget() { return targetChar_; };
};

