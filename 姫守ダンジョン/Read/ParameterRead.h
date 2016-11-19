//
//	@file	ParameterRead.h
//	@brief	�p�����[�^�ǂݍ���
//	@date	2016/11/14
//	@outher	�m�ȍ��c

#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

//
//	@brief	�v���C���[�E�ƃp�����[�^
class JobParameter
{
	char* name_;				//�E�Ɩ�
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//�ʏ�U����
	unsigned int specialAtk_;	//����U����
	unsigned int def_;			//�����
	float specialAttackTime_;	//�ҋ@����
	float chargeTime_;			//�`���[�W�^�C��
	float moveSpeed_;			//�ړ����x
	float specialMoveSpeed_;	//����ړ����x
	float weight_;				//�d��
	float attackReach_;			//�U�����[�`
	float attackRange_;			//�U���͈�
	float scale_;				//�X�P�[��
public:
	JobParameter(std::string str);
	const char* GetName()const { return name_; };				//���O�擾
	unsigned int GetHP()const { return hp_; };					//HP�擾
	unsigned int GetNormalAtk()const { return normalAtk_; };	//�ʏ�U���͎擾
	unsigned int GetSpAtk()const { return specialAtk_; };		//����U���͎擾
	unsigned int GetDefense()const { return def_; };			//����͎擾
	float GetChargeTime()const { return chargeTime_; };			//�`���[�W�^�C���擾
	float GetWaitTime()const { return specialAttackTime_; };	//�ҋ@���Ԏ擾
	float GetMoveSpeed()const { return moveSpeed_; };			//�ړ����x�擾
	float GetWeight()const { return weight_; };					//�d���擾
	float GetAttackReach_()const { return attackReach_; };		//�U�����[�`�擾
	float GetScale()const { return scale_; };					//�X�P�[���擾
};

//
//	@brief	�P�p�����[�^
class PrincessParameter
{
	float moveSpeed_;	//�ړ����x
	float weight_;		//�d��
public:
	PrincessParameter(std::string str);
	float GetMoveSpeed()const { return moveSpeed_; };	//�ړ����x�擾
	float GetWeight()const { return weight_; };			//�d���擾
};

//
//	@brief	�G�p�����[�^
class EnemyParameter
{
	char* name_;				//�G�̖��O
	unsigned int hp_;			//HP
	unsigned int normalAtk_;	//�ʏ�U��
	unsigned int def_;			//�����
	float moveSpeed_;			//�ړ��X�s�[�h
	float weight_;				//�d��
	float attackReach_;			//�U�����[�`
	float scale_;				//�X�P�[��
public:
	EnemyParameter(std::string str);
	const char* GetName()const { return name_; };				//���O�擾
	unsigned int GetHP()const { return hp_; };					//HP�擾
	unsigned int GetNormalAtk()const { return normalAtk_; };	//�ʏ�U���͎擾
	float GetMoveSpeed()const { return moveSpeed_; };			//�ړ��X�s�[�h�擾
	float GetWeight()const { return weight_; };					//�d���擾
	float GetAttackReach()const {return attackReach_; };		//�U�����[�`�擾
	float GetScale()const { return scale_; };					//�X�P�[���擾
};

//
//	@brief	�p�����[�^�ǂݍ��݃N���X
//	@note	�Ăяo�����s��
class ParameterRead
{
	JobParameter** jobParamList_;		//�E�ƃp�����[�^�i�[
	PrincessParameter* princessParam_;	//�P�p�����[�^�i�[
	EnemyParameter** enemyParamList_;	//�G�p�����[�^�i�[

	int jobCount_;		//�E�Ɛ�
	int enemyCount_;	//�G�̎�ސ�
public:
	ParameterRead();
	~ParameterRead();
	void SetJobParameter(const char* filePath);		//�E�ƃp�����[�^�ǂݍ���
	void SetPriceccParameter(const char* filePath);	//�P�p�����[�^�ǂݍ���
	void SetEnemyParameter(const char* filePath);	//�G�p�����[�^�ǂݍ���

	JobParameter* GetJobParamList(const char* name)const;					//�E�ƃp�����[�^�Ăяo��
	PrincessParameter* GetPrincessParam()const { return princessParam_; };	//�P�p�����[�^�Ăяo��
	EnemyParameter* GetEnemyParamList(const char* name)const;				//�G�p�����[�^�Ăяo��

};
