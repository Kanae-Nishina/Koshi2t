//
//	@file	ParameterRead.h
//	@brief	�p�����[�^�ǂݍ���
//	@date	2016/11/14
//	@author	�m�ȍ��c

#include "ParameterRead.h"

using namespace std;

//
//	@brief	JobParameter�R���X�g���N�^
JobParameter::JobParameter(string str)
	:hp_(0)
	, normalAtk_(0)
	, specialAtk_(0)
	, def_(0)
	, chainWeapon_(0)
	, spChainWeapon_(0)
	, invisibleTime_(0)
	, weaponDelTime_(0)
	, chargeTime_(0)
	, moveSpeed_(0)
	, specialMoveSpeed_(0)
	, attackReach_(0)
	, attackRange_(0)
	, knockbackSpeed_(0)
	, knockbackDist_(0)
	, weaponScale_(0)
{
	//�E�Ɩ��̎擾
	string temp = str;
	size_t comma = temp.find(',');
	string pull = temp.substr(0, comma);
	name_ = new char[comma + 1];
	memcpy(name_, pull.c_str(), comma + 1);
	temp = temp.substr(comma + 1);

	//HP�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	hp_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//�ʏ�U���擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	normalAtk_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//����U���擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	specialAtk_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//�`���[�W�^�C���擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	chargeTime_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//����͎擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	def_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//�ړ��X�s�[�h�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	moveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//����ړ��X�s�[�h�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	specialMoveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�U�����[�`�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	attackReach_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�U���͈͎擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	attackRange_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//����U���͈�
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	specialAtkRange_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�m�b�N�o�b�N���x
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	knockbackSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�m�b�N�o�b�N����
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	knockbackDist_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//���G����
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	invisibleTime_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//�ʏ펞��ѓ���A��������
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	chainWeapon_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//���ꎞ��ѓ���A��������
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	spChainWeapon_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//��ѓ���X�P�[��
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weaponScale_= atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//��ѓ�����Ŏ���
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weaponDelTime_ = atoi(pull.c_str());
	//temp = temp.substr(comma + 1);
}

//=====================================================================//

//
//	@brief	�P�p�����[�^�ǂݍ���
PrincessParameter::PrincessParameter(string str)
	:moveSpeed_(0)
	, weight_(0)
{
	//�E�Ɩ��̎擾
	string temp = str;
	size_t comma = temp.find(',');
	string pull = temp.substr(0, comma + 1);

	//�ړ��X�s�[�h�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	moveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�d���擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weight_ = atof(pull.c_str());
}

//=====================================================================//
//
//	@brief	EnemyParameter�R���X�g���N�^
EnemyParameter::EnemyParameter(string str)
{
	//���O�̎擾
	string temp = str;
	size_t comma = temp.find(',');
	string pull = temp.substr(0, comma);
	name_ = new char[comma + 1];
	memcpy(name_, pull.c_str(), comma + 1);
	temp = temp.substr(comma + 1);

	//HP�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	hp_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//�U���擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	atk_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//����͎擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	def_ = atoi(pull.c_str());
	temp = temp.substr(comma + 1);

	//�ړ��X�s�[�h�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	moveSpeed_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�d���擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	weight_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�U�����[�`�擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	attackReach_ = atof(pull.c_str());
	temp = temp.substr(comma + 1);

	//�X�P�[���擾
	comma = temp.find(',');
	pull = temp.substr(0, comma);
	scale_ = atof(pull.c_str());
}

//=======================================================================//

JobParameter** ParameterRead::jobParamList_;
PrincessParameter* ParameterRead::princessParam_;
EnemyParameter** ParameterRead::enemyParamList_;
int ParameterRead::jobCount_;
int ParameterRead::enemyCount_;

//
//	@brief	ParameterRead�R���X�g���N�^	
ParameterRead::ParameterRead()
{
}

//
//	@brief	ParameterRead�f�X�g���N�^	
ParameterRead::~ParameterRead()
{
	if (princessParam_ != nullptr)
	{
		delete princessParam_;
		princessParam_ = nullptr;
	}

	if (jobParamList_ != nullptr)
	{
		for (int i = 0; i < jobCount_; i++)
		{
			delete jobParamList_[i];
			jobParamList_[i] = nullptr;
		}
	}
	delete[] jobParamList_;
	jobParamList_ = nullptr;

	if (enemyParamList_ != nullptr)
	{
		for (int j = 0; j < enemyCount_; j++)
		{
			delete enemyParamList_[j];
			enemyParamList_[j] = nullptr;
		}
	}
	delete[] enemyParamList_;
	enemyParamList_ = nullptr;
}

//
//	@brief				�E�ƃp�����[�^�ǂݍ���
//	@param (filePath)	csv�t�@�C���p�X
void ParameterRead::SetJobParameter(/*const char* filePath*/)
{
	//�t�@�C���̓ǂݍ���
	ifstream ifs("./ReadData/JobParameterData.csv");
	if (!ifs)
	{
		return;
	}

	//��s�ڂ̓p�����[�^���Ȃ̂Ŕ�΂�
	string str;
	getline(ifs, str);

	//�f�[�^�̓ǂݍ���
	while (getline(ifs, str))
	{
		JobParameter* temp = new JobParameter(str);
		JobParameter** newList = new JobParameter*[jobCount_ + 1];

		if (jobCount_ > 0)
		{
			memcpy(newList, jobParamList_, sizeof(JobParameter**)*jobCount_);
		}

		newList[jobCount_] = temp;
		++jobCount_;
		delete[] jobParamList_;
		jobParamList_ = newList;
	}

	//�t�@�C�������
	ifs.close();
}

//
//	@brief				�P�p�����[�^�ǂݍ���
//	@param (filePath)	csv�t�@�C���p�X
void ParameterRead::SetPricessParameter(/*const char* filePath*/)
{
	////�t�@�C���̓ǂݍ���
	//ifstream ifs("");
	//if (!ifs)
	//{
	//	return;
	//}

	////��s�ڂ̓p�����[�^���Ȃ̂Ŕ�΂�
	//string str;
	//getline(ifs, str);

	////�f�[�^�̓ǂݍ���
	//getline(ifs, str);
	//princessParam_ = new PrincessParameter(str);

	////�t�@�C�������
	//ifs.close();
}

//
//	@brief				�G�p�����[�^�ǂݍ���
//	@param (filePath)	csv�t�@�C���p�X
void ParameterRead::SetEnemyParameter(/*const char* filePath*/)
{
	//�t�@�C���̓ǂݍ���
	ifstream ifs("./ReadData/EnemyParameterData.csv");
	if (!ifs)
	{
		return;
	}

	//��s�ڂ̓p�����[�^���Ȃ̂Ŕ�΂�
	string str;
	getline(ifs, str);

	//�f�[�^�̓ǂݍ���
	while (getline(ifs, str))
	{
		EnemyParameter* temp = new EnemyParameter(str);
		EnemyParameter** newList = new EnemyParameter*[enemyCount_ + 1];

		if (enemyCount_ > 0)
		{
			memcpy(newList, enemyParamList_, sizeof(EnemyParameter**)*enemyCount_);
		}

		newList[enemyCount_] = temp;
		++enemyCount_;
		delete[] enemyParamList_;
		enemyParamList_ = newList;
	}

	//�t�@�C�������
	ifs.close();
}

//
//	@brief	�E�Ɛ��̎擾
int ParameterRead::GetJobCount()const
{
	return jobCount_;
}

//
//	@brief	�G�l�~�[���̎擾
int ParameterRead::GetEnemyCount()const
{
	return enemyCount_;
}

//
//	@brief			�E�ƃp�����[�^�擾
//	@param (name)	�E�Ɩ�
JobParameter* ParameterRead::GetJobParamList(const char* name)const
{
	for (int i = 0; i < jobCount_; i++)
	{
		if (strcmp(name, jobParamList_[i]->GetName()) == 0)
		{
			return jobParamList_[i];
		}
	}

	return nullptr;
}

//
//	@brief			�G�p�����[�^�擾
//	@param (name)	�G�̖��O
EnemyParameter* ParameterRead::GetEnemyParamList(const char* name)const
{
	for (int i = 0; i < enemyCount_; i++)
	{
		if (strcmp(name, enemyParamList_[i]->GetName()) == 0)
		{
			return enemyParamList_[i];
		}
	}
	return nullptr;
}