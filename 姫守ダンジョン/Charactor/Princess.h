//
//	@file	Princess.h
//	@brief	�P�N���X
//	@date	2016/12/01
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#pragma once
#include <list>
#include "./CharactorManager.h"
#include "./Player/PlayerManager.h"
#include "./../Stage/Spawn.h"


class Princess :public CharactorManager
{
private:
	std::vector<Spawn*> spawnPosList_;
	Spawn* sealSpawn_;
	std::vector<PlayerManager*> deadCharaList_;	//���񂾃v���C���[���X�g
	D3DXVECTOR3 destination_;					//�ړ��ړI�n
	int destinationSpaceNo_;					//�ړ��ړI�n��Ԕԍ�
	float moveSpeed_;							//�ړ����x
	unsigned int sealTime_;						//����ɂ����鎞��
	unsigned int revivalTime_;					//�h���ɂ����鎞��
	bool sealFlg_;
	bool resFlg_;

	virtual void Move(float speed);				//�ړ�
	//virtual void Motion_Update();				//���[�V�����X�V
	virtual void Dead() {};
	virtual void Attack() {};
	void Seal();					//����
	void Resuscitation();			//�h��
	virtual void SetParameter(char* name);
public:
	Princess();
	virtual ~Princess();

	Spawn* SealSpawn();
	virtual void Reset();
	virtual void CharaUpdate();						//�X�V
	virtual void DamageCalc(unsigned int atk);		//�_���[�W�v�Z
	void SetDestination(D3DXVECTOR3 pos);			//�ړI�n�Z�b�g
	void SetDeadCharaList(PlayerManager* chara);
	void SetSpawn(std::vector<Spawn*> spawn);
	void DeadMotion();
};

