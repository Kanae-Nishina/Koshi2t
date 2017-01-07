#pragma once
#include "./tinyxml2.h"

using namespace tinyxml2;

//
//	@brief	���[�V�����̑���
struct MotionAttr
{
	char name_[30];		//���[�V������
	unsigned int id_;	//���[�V�����ԍ�
	unsigned int frame_;	//�t���[����
};

//
//	@brief	���[�V�����f�[�^
class Motion
{
private:
	char name_[30];				//���[�V�����g�p�Җ�
	MotionAttr** motionList_;	//���[�V�����������X�g
	unsigned int count_;		//���[�V������
public:
	Motion(XMLElement* elemnt);
	const char* GetName()const { return name_; };
	const MotionAttr* GetMotion(char* name)const;
	
};

//
//	@brief	���[�V�������X�g�ǂݍ��݃N���X
class MotionRead
{
private:
	static Motion** playermMotionList_;	//�v���C���[���[�V�������X�g
	static Motion** enemyMotionList_;		//�G�l�~�[���[�V�������X�g

	static unsigned int countP_;
	static unsigned int countE_;
public:
	MotionRead();
	~MotionRead();

	static void PlayerMotionRead();
	static void EnemyMotionRead();
	Motion* GetMotionUser(const char* name);
};