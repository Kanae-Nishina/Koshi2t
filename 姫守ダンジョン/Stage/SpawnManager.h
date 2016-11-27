#pragma once
#include "./../Origin.h"
#include "./Spawn.h"

template<class temp>
class SpawnManager
{
private:
	char stageTye[30];					//���݂̃X�e�[�W�^�C�v
	std::vector<Spawn> spawnList_;		//���ݑ��݂��Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn> functionList_;	//�@�\���Ă���X�|�[���Q�[�g���X�g
	std::vector<Spawn> renderList_;		//�`�悷��X�|�[���Q�[�g���X�g���X�g
	std::vector<Spawn> killList_;		//���ł���X�|�[���Q�[�g���X�g

	void SpawnSet();	//�X�|�[���Q�[�g�̏���
public:
	std::vector<temp> OutEnemy();
	void Init();
	void Update();
	void Render();
};