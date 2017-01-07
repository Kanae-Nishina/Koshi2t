//
//	@file	XFileRead.h
//	@brief	X�t�@�C���ǂݍ���
//	@date	2016/11/07
//	@author	�m�ȍ��c

#include "XFileRead.h"

//
//	@brief				XFile�N���X�R���X�g���N�^
//	@param (element)	�ǂݍ��ޗv�f
XFile::XFile(XMLElement* element, const char* type)
{
	//�^�C�v�擾
	memset(type_, 0, sizeof(type_));
	strcpy_s(type_, sizeof(type_), type);

	//�t�@�C�����擾
	memset(fileName_, 0, sizeof(fileName_));
	strcpy_s(fileName_, sizeof(fileName_) - 1, element->Attribute("fileName"));

	//�L�����l�[���擾
	memset(charName_, 0, sizeof(charName_));
	strcpy_s(charName_, sizeof(charName_) - 1, element->Attribute("charName"));

	if (strcmp(type, "Player") == 0)
	{
		filePath_ = "./Model/XFiles/Player/"+(std::string)fileName_;
	}
	else if (strcmp(type, "Enemy") == 0)
	{
		filePath_ = "./Model/XFiles/Enemy/" + (std::string)fileName_;
	}
	else if (strcmp(type, "Princess") == 0)
	{
		filePath_ = "./Model/XFiles/Princess/" + (std::string)fileName_;
	}
	else
	{
		filePath_ = "./Model/XFiles/Stage/" + (std::string)fileName_;
	}
}

//
//	@brief	XFileRead�N���X�R���X�g���N�^
XFileRead::XFileRead()
	:count_(0)
	, xfileList_(0)
{
}

//
//	@brief	XFileRead�N���X�f�X�g���N�^
XFileRead::~XFileRead()
{
	for (int i = 0; i < count_; i++)
	{
		delete xfileList_[i];
	}
	delete[] xfileList_;
}

//
//	@brief	X�t�@�C���̏��ǂݍ���
void XFileRead::ReadXFilePath()
{
	tinyxml2::XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();
	xml.InsertEndChild(decl);

	//�t�@�C���ǂݍ���
	xml.LoadFile("./ReadData/XFileName.xml");

	//X�t�@�C���̖��O�ƃL�����N�^�[�l�[���̎擾
	for (XMLElement* models = xml.FirstChildElement("Models"); models != NULL; models = models->NextSiblingElement("Models"))
	{
		const char* type = models->Attribute("Type");
		for (XMLElement* model = models->FirstChildElement("model"); model != NULL; model = model->NextSiblingElement("model"))
		{
			XFile* temp = new XFile(model, type);
			XFile** newList = new XFile*[count_ + 1];

			if (count_ > 0)
			{
				memcpy(newList, xfileList_, sizeof(XFile**)*count_);
			}
			newList[count_] = temp;
			++count_;
			delete[] xfileList_;
			xfileList_ = newList;
		}
	}
}

//
//	@brief			x�t�@�C���̃p�X���擾
//	@param (name)	�擾���郂�f����
XFile* XFileRead::GetXFile(const char* name)
{
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(xfileList_[i]->GetCharName(), name) == 0)
		{
			return xfileList_[i];
		}
	}

	return nullptr;
}

//
//	@brief			�X�e�[�W���f���̏��擾
std::vector<XFile*> XFileRead::GetStageFile()
{
	std::vector<XFile*> temp;
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(xfileList_[i]->GetType(), "Stage") == 0)
		{
			temp.push_back(xfileList_[i]);
		}
	}
	return temp;
}

std::vector<XFile*> XFileRead::GetModelFile()
{
	std::vector<XFile*> temp;
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(xfileList_[i]->GetType(), "Stage") != 0
			&& strcmp(xfileList_[i]->GetType(), "Spawn") != 0)
		{
			temp.push_back(xfileList_[i]);
		}
	}
	return temp;
}

////
////	@brief	x�t�@�C���̓ǂݍ���
//void XFileRead::ReadXFile(CD3DXMESH_ANIM* mesh, const char*name)
//{
//	XFile* file = GetXFile(name);
//
//	/*if (FAILED((mesh->Init(Origin::GetInstance().m_hWnd, Origin::GetInstance().m_pDevice, Origin::GetInstance().m_pDeviceContext, fileName, texPath))))
//	{
//		return;
//	}*/
//}