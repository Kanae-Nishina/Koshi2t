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
	char* name_;						//�E�Ɩ�
	unsigned int hp_;					//HP
	unsigned int normalAtk_;			//�ʏ�U����
	unsigned int specialAtk_;			//����U����
	unsigned int def_;					//�����
	unsigned int chainWeapon_;			//�A����ѓ���ݒu��
	unsigned int spChainWeapon_;		//���ꎞ�A����ѓ���ݒu��
	unsigned int specialAttackTime_;	//����U������
	unsigned int invisibleTime_;		//���G����
	unsigned int weaponDelTime_;		//��ѓ�����Ŏ���
	unsigned int chargeTime_;			//�`���[�W�^�C��
	float moveSpeed_;					//�ړ����x
	float specialMoveSpeed_;			//����ړ����x
	float weight_;						//�d��
	float attackReach_;					//�U�����[�`
	float attackRange_;					//�U���͈�
	float specialAtkRange_;				//����U�����͈�
	float scale_;						//�X�P�[��
	float knockbackSpeed_;				//�m�b�N�o�b�N������X�s�[�h
	float knockbackDist_;				//�m�b�N�o�b�N���鋗��
	float weaponScale_;					//��ѓ���T�C�Y
	float weaponHitReach_;				//��ѓ���Փ˔͈�
	float weaponDelDist_;				//��ѓ�����ŋ���
public:
	JobParameter(std::string str);
	const char* GetName()const { return name_; };					//���O�擾
	unsigned int GetHP()const { return hp_; };						//HP�擾
	unsigned int GetNormalAtk()const { return normalAtk_; };		//�ʏ�U���͎擾
	unsigned int GetSpAtk()const { return specialAtk_; };			//����U���͎擾
	unsigned int GetDefence()const { return def_; };				//����͎擾
	unsigned int GetChainWeapon()const { return chainWeapon_; };	//�A����ѓ���ݒu���擾
	unsigned int GetSpChainWeapon()const { return spChainWeapon_; };//���ꎞ�A����ѓ���ݒu���擾
	unsigned int GetSpAtkTime()const { return specialAttackTime_; };//�ҋ@���Ԏ擾
	unsigned int GetInvisivleTime()const { return invisibleTime_; };//���G���Ԏ擾
	unsigned int GetWeaponDelTime()const { return weaponDelTime_; };//��ѓ�����Ŏ���
	unsigned int GetChargeTime()const { return chargeTime_; };		//�`���[�W�^�C���擾
	float GetMoveSpeed()const { return moveSpeed_; };				//�ړ����x�擾
	float GetSpMoveSpeed()const { return specialMoveSpeed_; };		//����ړ����x�擾
	float GetWeight()const { return weight_; };						//�d���擾
	float GetAttackReach()const { return attackReach_; };			//�U�����[�`�擾
	float GetAttackRange()const { return attackRange_; };			//�U���͈͎擾
	float GetSpAtkRange()const { return specialAtkRange_; };		//����U���͈�
	float GetScale()const { return scale_; };						//�X�P�[���擾
	float GetKnockBackSpeed()const { return knockbackSpeed_; };		//�m�b�N�o�b�N�X�s�[�h�擾
	float GetKnockBackDist()const { return knockbackDist_; };		//�m�b�N�o�b�N�����擾
	float GetWeaponScale()const { return weaponScale_; };			//��ѓ���X�P�[���擾
	float GetWeaponHitReach()const { return weaponHitReach_; };		//��ѓ���Փ˔͈�
	float GetWeaponDelDist()const { return weaponDelDist_; };		//��ѓ�����ŋ���
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
	unsigned int atk_;			//�ʏ�U��
	unsigned int def_;			//�����
	float moveSpeed_;			//�ړ��X�s�[�h
	float weight_;				//�d��
	float attackReach_;			//�U�����[�`
	float scale_;				//�X�P�[��
public:
	EnemyParameter(std::string str);
	const char* GetName()const { return name_; };				//���O�擾
	unsigned int GetHP()const { return hp_; };					//HP�擾
	unsigned int GetAtk()const { return atk_; };				//�ʏ�U���͎擾
	unsigned int GetDefence()const { return def_; };			//����͎擾
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

	int GetJobCount()const;
	int GetEnemyCount()const;
	JobParameter* GetJobParamList(const char* name)const;					//�E�ƃp�����[�^�Ăяo��
	PrincessParameter* GetPrincessParam()const { return princessParam_; };	//�P�p�����[�^�Ăяo��
	EnemyParameter* GetEnemyParamList(const char* name)const;				//�G�p�����[�^�Ăяo��
	 
};
