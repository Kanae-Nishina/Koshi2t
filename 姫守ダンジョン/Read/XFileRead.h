//
//	@file	XFileRead.h
//	@brief	X�t�@�C���ǂݍ���
//	@date	2016/11/07
//	@outher	�m�ȍ��c

#pragma once
#include "./../Origin.h"
#include "./../Mesh/CD3DXMesh_Anim.h"
#include "./tinyxml2.h"

using namespace tinyxml2;

//
//	@brief	�ǂݍ���X�t�@�C���̏��N���X
class XFile
{
	char type_[30];
	char fileName_[30];
	char charName_[30];
public:
	XFile(XMLElement* element,const char* type);

	const char* GetType()const { return type_; };
	const char* GetFileName()const { return fileName_; };
	const char* GetCharName()const { return charName_; };
};

//
//	@brief	X�t�@�C���ǂݍ��݃N���X
class XFileRead
{
	XFile** xfileList_;				//X�t�@�C���Ǘ�
	int count_;						//�ǂݍ���X�t�@�C����

public:
	XFileRead();
	~XFileRead();

	XFile* GetXFile(const char*);	//X�t�@�C���̃p�X���擾
	void ReadXFilePath();			//X�t�@�C���̃p�X���ǂݍ���
	//void ReadXFile(CD3DXMESH_ANIM* mesh,const char* name);			//X�t�@�C���̓ǂݍ���
	int GetCount()const { return count_; };
};

