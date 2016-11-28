#include "./Spawn.h"

//
//	@brief	�R���X�g���N�^
Spawn::Spawn()
{
	spawnID_ = 0;
	amount_ = 10;
	m_vPos = { 0,0,0 };
}

//
//	@brief	�f�X�g���N�^
Spawn::~Spawn()
{

}

//
//	@brief	�X�|�[���̏�����
void Spawn::SpawnInit(const char* name)
{

	char FileName[80];
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Stage/");
	strcat_s(FileName, sizeof(FileName), name);
	if (LoadXMesh(FileName))
	{
		return;
	}

	m_vPos = { 0,0,0 };
	spawnID_ = 0;
	amount_ = 20;

	memset(enemyName_, 0, sizeof(enemyName_));
	strcpy_s(enemyName_, sizeof(enemyName_), "t01.X");

}

//
//	@brief	�G�l�~�[���X�g�̃Z�b�g
void Spawn::ListSet(ParameterRead* param, CharactorManager* target)
{
	srand((unsigned)time(NULL));
	int range = 10;
	for (int i = 0; i < amount_; i++)
	{
		EnemyJobManager* enemy = new Slim;
		enemy->SetParameter(param->GetEnemyParamList("�X���C��"));
		enemy->SetTarget(target);
		enemy->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
		enemy->m_Pos = D3DXVECTOR3(rand() % range + (m_vPos.x-range/2), 0, rand() % range +(m_vPos.z-range/2));
		insEnemyList_.push_back(enemy);
	}
}

//
//	@brief	�G�l�~�[�̃X�|�[��
std::vector<EnemyJobManager*> Spawn::EnemySpawn()
{
	return insEnemyList_;
}

//
//	@brief	�G�l�~�[���X�g�̃��Z�b�g
void Spawn::ListReset()
{
	insEnemyList_.clear();
}

//
//	@brief	�`��
void Spawn::SpawnRender()
{
	Render(m_vPos,D3DXVECTOR3(0,0,0),0.2);
}