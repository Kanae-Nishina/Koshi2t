#include "MotionRead.h"

Motion** MotionRead::playermMotionList_;
Motion** MotionRead::enemyMotionList_;
unsigned int MotionRead::countP_;
unsigned int MotionRead::countE_;

//
//	@brief	���[�V�����N���X�R���X�g���N�^
Motion::Motion(XMLElement* element)
	:count_(0)
	, motionList_(0)
{
	//���[�V�����g�p�Җ�
	memset(name_, 0, sizeof(name_));
	memcpy(name_, element->Attribute("name"), sizeof(name_));

	for (XMLElement* motion = element->FirstChildElement("motion"); motion != NULL; motion = motion->NextSiblingElement("motion"))
	{
		MotionAttr* temp = new MotionAttr;
		MotionAttr** newList = new MotionAttr*[count_ + 1];

		memset(temp->name_, 0, sizeof(temp->name_));
		memcpy(temp->name_, motion->Attribute("name"), sizeof(temp->name_));

		temp->id_ = atoi(motion->Attribute("id"));
		temp->frame_ = atoi(motion->Attribute("frame"));

		if (count_ > 0)
		{
			memcpy(newList, motionList_, sizeof(MotionAttr**)*count_);
		}

		newList[count_] = temp;
		++count_;
		delete[] motionList_;
		motionList_ = newList;
	}
}

//
//	@brief	���[�V�����̎擾
const MotionAttr* Motion::GetMotion(char* name)const
{
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(name, motionList_[i]->name_) == 0)
		{
			return motionList_[i];
		}
	}

	return nullptr;
}


//
//	@brief	���[�V�����ǂݍ��݃N���X�̃R���X�g���N�^
MotionRead::MotionRead()
{
}

//
//	@brief	���[�V�����ǂݍ��݃N���X�̃f�X�g���N�^
MotionRead::~MotionRead()
{
	if (playermMotionList_ != nullptr)
	{
		for (int i = 0; i < countP_; i++)
		{
			delete playermMotionList_[i];
			playermMotionList_[i] = nullptr;
		}
		delete[] playermMotionList_;
		playermMotionList_ = nullptr;
	}

	if (enemyMotionList_ != nullptr)
	{
		for (int i = 0; i < countE_; i++)
		{
			delete enemyMotionList_[i];
			enemyMotionList_[i] = nullptr;
		}
		delete[] enemyMotionList_;
		enemyMotionList_ = nullptr;
	}
}

//
//	@brief	�v���C���[���[�V�����f�[�^�ǂݍ���
void MotionRead::PlayerMotionRead()
{
	XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();

	//�t�@�C���ǂݍ���
	xml.LoadFile("./ReadData/Motion.xml");

	//���[�V�������̎擾
	for (XMLElement* job = xml.FirstChildElement("Job"); job != NULL; job = job->NextSiblingElement("Job"))
	{
		Motion* temp = new Motion(job);
		Motion** newList = new Motion*[countP_ + 1];

		if (countP_ > 0)
		{
			memcpy(newList, playermMotionList_, sizeof(Motion**)*countP_);
		}
		newList[countP_] = temp;
		++countP_;
		delete[] playermMotionList_;
		playermMotionList_ = newList;
	}
}

//
//	@brief	�G�l�~�[�̃��[�V�����f�[�^�ǂݍ���
void MotionRead::EnemyMotionRead()
{
	XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();

	//�t�@�C���ǂݍ���
	xml.LoadFile("./ReadData/EnemyMotion.xml");

	//���[�V�������̎擾
	for (XMLElement* job = xml.FirstChildElement("Job"); job != NULL; job = job->NextSiblingElement("Job"))
	{
		Motion* temp = new Motion(job);
		Motion** newList = new Motion*[countE_ + 1];

		if (countE_ > 0)
		{
			memcpy(newList, enemyMotionList_, sizeof(Motion**)*countE_);
		}
		newList[countE_] = temp;
		++countE_;
		delete[] enemyMotionList_;
		enemyMotionList_ = newList;
	}
}

//
//	@brief	���[�V�����g�p�Ҏ擾
Motion* MotionRead::GetMotionUser(const char* name)
{

	for (int i = 0; i < countP_; i++)
	{
		if (strcmp(name, playermMotionList_[i]->GetName()) == 0)
		{
			return playermMotionList_[i];
		}
	}

	for (int i = 0; i < countE_; i++)
	{
		if (strcmp(name, enemyMotionList_[i]->GetName()) == 0)
		{
			return enemyMotionList_[i];
		}
	}
	return nullptr;

}