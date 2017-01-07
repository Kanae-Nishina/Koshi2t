#include "./SpawnGateRead.h"


//
//	@brief	�X�|�[���Q�[�g�N���X�̃R���X�g���N�^
SpawnGate::SpawnGate(XMLElement* element)
	:spawnGateList_(0)
	,count_(0)
{
	memset(stageName_, 0, sizeof(stageName_));
	strcpy_s(stageName_, sizeof(stageName_), element->Attribute("Type"));

	for (XMLElement* spawn = element->FirstChildElement("spawn"); spawn != NULL; spawn = spawn->NextSiblingElement("spawn"))
	{
		SpawnGateAttr* temp = new SpawnGateAttr;

		temp->id_ = atoi(spawn->Attribute("id"));
		memset(temp->enemyName_, 0, sizeof(temp->enemyName_));
		strcpy_s(temp->enemyName_, sizeof(temp->enemyName_), spawn->Attribute("enemyName"));
		temp->amount_ = atoi(spawn->Attribute("amount"));
		temp->interval_ = atoi(spawn->Attribute("interval"));

		XMLElement* pos = spawn->FirstChildElement("pos");
		PosRead(pos, temp->pos_);
		/*temp->pos_.x = atof(pos->Attribute("x"));
		temp->pos_.y = atof(pos->Attribute("y"));
		temp->pos_.z = atof(pos->Attribute("z"));*/

		pos = pos->NextSiblingElement("leftBack");
		PosRead(pos, temp->leftBack_);
		/*temp->leftBack_.x = atof(pos->Attribute("x"));
		temp->leftBack_.y = atof(pos->Attribute("y"));
		temp->leftBack_.z = atof(pos->Attribute("z"));*/

		pos = pos->NextSiblingElement("rightFront");
		PosRead(pos, temp->rightFront_);
		/*temp->leftBack_.x = atof(pos->Attribute("x"));
		temp->leftBack_.y = atof(pos->Attribute("y"));
		temp->leftBack_.z = atof(pos->Attribute("z"));*/

		SpawnGateAttr** newList = new SpawnGateAttr*[count_ + 1];

		if (count_ > 0)
		{
			memcpy(newList, spawnGateList_, sizeof(SpawnGateAttr**)*count_);
		}

		newList[count_] = temp;
		++count_;
		delete[] spawnGateList_;
		spawnGateList_ = newList;
	}
}

//
//	@brief	�X�|�[���Q�[�g�N���X�̃f�X�g���N�^
SpawnGate::~SpawnGate()
{
	/*for (int i = 0; i < count_; i++)
	{
		delete spawnGateList_[i];
		spawnGateList_[i] = nullptr;
	}
	delete[] spawnGateList_;
	spawnGateList_ = nullptr;*/
}

void SpawnGate::PosRead(XMLElement* element,D3DXVECTOR3 &pos)
{
	pos.x = atof(element->Attribute("x"));
	pos.y = atof(element->Attribute("y"));
	pos.z = atof(element->Attribute("z"));
}

//
//	@brief	1�X�e�[�W��ɑ��݂���X�|�[���Q�[�g���̎擾
std::vector<SpawnGateAttr*> SpawnGate::GetStageAllSpawnGate()
{
	std::vector<SpawnGateAttr*> temp;
	for (int i = 0;i < count_; i++)
	{
		temp.push_back(spawnGateList_[i]);
	}

	return temp;
}


//
//	@brief	�X�|�[���Q�[�g�ǂݍ��݃N���X�R���X�g���N�^
SpawnGateRead::SpawnGateRead()
	:spawnGateList_(0)
	,count_(0)
{
}

//
//	@brief	�X�|�[���Q�[�g�ǂݍ��݃N���X�f�X�g���N�^
SpawnGateRead::~SpawnGateRead()
{
	for (int i = 0; i < count_; i++)
	{
		delete spawnGateList_[i];
		spawnGateList_[i] = nullptr;
	}
	delete[] spawnGateList_;
	spawnGateList_ = nullptr;
}

//
//	@brief	�X�|�[���Q�[�g�̓ǂݍ���
void SpawnGateRead::SpawnGate_Read()
{
	tinyxml2::XMLDocument xml;
	XMLDeclaration* decl = xml.NewDeclaration();

	//�t�@�C���ǂݍ���
	xml.LoadFile("./ReadData/Spawn.xml");

	//�X�|�[���Q�[�g���̎擾
	for (XMLElement* stage = xml.FirstChildElement("Stage"); stage != NULL; stage = stage->NextSiblingElement("Stage"))
	{
		SpawnGate* temp = new SpawnGate(stage);
		SpawnGate** newList = new SpawnGate*[count_ + 1];

		if (count_ > 0)
		{
			memcpy(newList, spawnGateList_, sizeof(SpawnGate**)*count_);
		}
		newList[count_] = temp;
		++count_;
		delete[] spawnGateList_;
		spawnGateList_ = newList;
	}
}

//
//	@brief	1�X�e�[�W�̃X�|�[���Q�[�g���̎擾
SpawnGate* SpawnGateRead::GetSpawnGate(const char* stageName)
{
	for (int i = 0; i < count_; i++)
	{
		if (strcmp(stageName, spawnGateList_[i]->GetStageName()) == 0)
		{
			return spawnGateList_[i];
		}
	}

	return nullptr;
}