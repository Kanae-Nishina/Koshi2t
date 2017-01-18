#pragma once
#include <vector>
#include <d3dx9math.h>
#include "./tinyxml2.h"

using namespace tinyxml2;

//
//	@brief	�X�|�[���Q�[�g�̑���
struct SpawnGateAttr
{
	unsigned int id_;			//�X�|�[���Q�[�g�ԍ�
	D3DXVECTOR3 pos_;			//���W
	D3DXVECTOR3 leftBack_;		//�o���͈͍��W����
	D3DXVECTOR3 rightFront_;	//�o���͈͍��W�E��O
	char enemyName_[30];		//�o������G�̖��O
	unsigned int amount_;		//��x�ɏo�����鐔
	unsigned int interval_;		//���ɏo������܂ł̎���(�b)
};

//
//	@brief	�X�|�[���Q�[�g�N���X(1�X�e�[�W��)
class SpawnGate
{
private:
	char stageName_[30];
	unsigned int count_;
	SpawnGateAttr** spawnGateList_;
	std::vector<D3DXVECTOR3> busStop_;

	void PosRead(XMLElement* element, D3DXVECTOR3 &pos);
public:
	SpawnGate(XMLElement* element);
	~SpawnGate();
	const char* GetStageName()const { return stageName_; };
	int GetCount()const { return count_; };
	std::vector<D3DXVECTOR3> GetBusStop()const { return busStop_; };
	std::vector<SpawnGateAttr*> GetStageAllSpawnGate();
};

//
//	@brief	�X�|�[���Q�[�g�ǂݍ��݃N���X
class SpawnGateRead
{
private:
	SpawnGate** spawnGateList_;		//�S�ẴX�|�[���Q�[�g�̃��X�g
	unsigned int count_;			//���ׂẴX�|�[���Q�[�g��
public:
	SpawnGateRead();
	~SpawnGateRead();

	void SpawnGate_Read();							//�X�|�[���Q�[�g���̓ǂݍ���
	SpawnGate* GetSpawnGate(const char* stageName);	//1�X�e�[�W�̃X�|�[���Q�[�g���̌Ăяo��
};