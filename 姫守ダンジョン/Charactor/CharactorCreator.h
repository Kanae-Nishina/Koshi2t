//
//	@file	CharactorCreator.h
//	@brief	�L�����N�^�[�����N���X
//	@date	2016/11/14
//	@author	�m�ȍ��c

#pragma once
#include <map>
#include <string>

typedef std::string ObjectType;

//
//	@brief	������x�[�X
template<class Base>
class CreatorBase
{
public:
	virtual ~CreatorBase() {};
	virtual Base* Create() const = 0;
};

//
//	@brief	��������^�Ɗ��N���X�w��
template<class Product,class Base>
class Creator :public CreatorBase<Base>
{
public:
	virtual Base* Create() const { return new Product; };
};

//
//	@brief	�����Ɠo�^
template<class Base>
class CharactorCreator
{
private:
	typedef std::map<ObjectType, CreatorBase<Base> *> CreatorMap;
	CreatorMap creatorMap_;
public:
	//�L�����N�^�[�̐�������
	Base* Create(ObjectType type);

	//�������o�^
	bool Register(ObjectType, CreatorBase<Base>*creator);
};

//
//	@brief ������o�^����
template<class Base>
bool CharactorCreator<Base>::Register(ObjectType, CreatorBase<Base>*creator)
{
	// �f�[�^���Ȃ��ꍇ�́A�R���e�i�̏I�[���Ԃ��Ă���
	CreatorMap::iterator it = creatorMap_.find(type);

	// ���Ƀf�[�^������ꍇ�͐�������폜����
	if (it != creatorMap_.end())
	{
		delete creator;
		return false;
	}

	creatorMap_[type] = creator;
	return true;
}

//
//	@brief	����
template<class Base>
Base* Create(ObjectType type)
{
	CreatorMap::iterator it = creatorMap_.find(type);

	// �����킪�Ȃ���Ύ��s
	if (it == creatorMap_.end())
	{
		return nullptr;
	}

	CreatorBase<Base>* creator = (*it).second;
	return creator->Create();
}