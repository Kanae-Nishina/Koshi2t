//
//	@file	Main_Scene.cpp
//	@brief	�Q�[�����C���V�[��
//	@date	2016/11/08
//	@author	�m�ȍ��c
//	@author �g�z��R(�G�t�F�N�g�EUI)

//#include "./Main_Scene.h"
#include "./../SceneParts/Main_Scene.h"

//
//	@brief	�R���X�g���N�^
Main_Scene::Main_Scene()
{
	stage_ = new Stage;
	
	camera_ = new Camera;

	//Title_UI["TITLE_UI"] = new TD_Graphics;
	debugText_ = new D3D11_TEXT;
}

//
//	@brief	�f�X�g���N�^
Main_Scene::~Main_Scene()
{
	//delete stage_;
	//stage_ = nullptr;

	//delete spawnManager_;
	//spawnManager_ = nullptr;


	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(player_[i]);
	}
	SAFE_DELETE(princess_);
	//SAFE_DELETE(virEnemy_);
	//SAFE_DELETE(slime_);
	//delete debugText_;
	//debugText_ = nullptr;

	//delete xfile;
	//xfile = nullptr;
	//delete parameter;
	//parameter = nullptr;

	delete camera_;
	camera_ = nullptr;

	/*delete uisword_;
	uisword_ = nullptr;
	delete uiseeld_;
	uiseeld_ = nullptr;
	delete uimagic_;
	uimagic_ = nullptr;
	delete uibom_;
	uibom_ = nullptr;*/

	/*delete uititle_;
	uititle_ = nullptr;*/
}

//
//	@brief						������
//	@param (m_hWnd)				�E�B���h�E�̃n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
void Main_Scene::Init(/*HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext*/)
{
	

	spawnManager_ = new SpawnManager;
	stage_->Init("�X�e�[�W5");
	spawnManager_->Init("�X�|�[��");

	JobManager* ply;
	for (int i = 0; i < 4; i++)
	{
		player_.push_back(ply);
	}

	player_[Player1] = SetCharaJob(CharactorCreator::player1_, Player1);
	player_[Player2] = SetCharaJob(CharactorCreator::player2_, Player2);
	player_[Player3] = SetCharaJob(CharactorCreator::player3_, Player3);
	player_[Player4] = SetCharaJob(CharactorCreator::player4_, Player4);
	princess_ = new Princess;

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(player_[i]);
	}
	charList_.push_back(princess_);
	player_[Player1]->CharaInit(CharactorCreator::player1_);
	player_[Player1]->m_Pos = D3DXVECTOR3(0, 0, 0);
	player_[Player2]->CharaInit(CharactorCreator::player2_);
	player_[Player2]->m_Pos = D3DXVECTOR3(-1.5, 0, -10);
	player_[Player3]->CharaInit(CharactorCreator::player3_);
	player_[Player3]->m_Pos = D3DXVECTOR3(1.5, 0, -10);
	player_[Player4]->CharaInit(CharactorCreator::player4_);
	player_[Player4]->m_Pos = D3DXVECTOR3(3, 0, -10);

	princess_->CharaInit("�P");
	princess_->m_Pos = D3DXVECTOR3(0, 0, -12);
	princess_->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	princess_->SetSpawn(spawnManager_->GetSpawnList());

	time_ = 0;
	scene_ = StartS;
}

//
//	@brief	�E�ƃZ�b�g
JobManager* Main_Scene::SetCharaJob(char* name, CharaType type)
{
	JobManager* temp;
	if (strcmp(name, "���m") == 0)
	{
		temp = new SwordMan(type);
	}
	else if (strcmp(name, "���m") == 0)
	{
		temp = new ShieldMan(type);
	}
	else if (strcmp(name, "���e�m") == 0)
	{
		temp = new Bomber(type);
	}
	else if (strcmp(name, "�����m") == 0)
	{
		temp = new Witch(type);
	}

	return temp;
}

//
//	@brief	���
void Main_Scene::Destroy()
{
}

////
////	@brief	�f�o�b�O�p������
//HRESULT Main_Scene::DebugInit(ID3D11DeviceContext* m_pDeviceContext)
//{
//	debugText_ = new D3D11_TEXT;
//	ID3D11DeviceContext* deviceContext_ = m_pDeviceContext;
//	D3DXVECTOR4 vColor(0, 0, 0, 1);
//	if (FAILED(debugText_->Init(deviceContext_, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor)))
//	{
//		return E_FAIL;
//	}
//	return S_OK;
//}

//HRESULT Main_Scene::EffectInit(ID3D11DeviceContext* m_pDeviceContext)
//{
//	
//	deviceContext_ = m_pDeviceContext;
//	float scaleF = 8;
//	D3DXVECTOR3 scale(scaleF, 5, scaleF);
//
//	uititle_ = new D3D11_SPRITE;
//	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
//	if (FAILED(uititle_->CreateEffects(L"./Effect/Effect_Tex/title.png", true, D3DXVECTOR2(1, 1), 1,D3DXVECTOR3(20,20,20))))
//	{
//		return E_FAIL;
//	}
//
//	uisword_ = new D3D11_SPRITE;
//	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
//	if (FAILED(uisword_->CreateEffects(L"./Effect/Effect_Tex/UISword.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//	uiseeld_ = new D3D11_SPRITE;
//	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
//	if (FAILED(uiseeld_->CreateEffects(L"./Effect/Effect_Tex/UISeeld.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//	uimagic_ = new D3D11_SPRITE;
//	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
//	if (FAILED(uimagic_->CreateEffects(L"./Effect/Effect_Tex/UIMagic.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//	uibom_ = new D3D11_SPRITE;
//	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
//	if (FAILED(uibom_->CreateEffects(L"./Effect/Effect_Tex/UIBom.png", true, D3DXVECTOR2(1, 1), 5, scale)))
//	{
//		return E_FAIL;
//	}
//
//	
//
//	return S_OK;
//}

//
//	@brief	�X�V
void Main_Scene::Update()
{
	switch (scene_)
	{
	case MainS:
		GameMain();
		break;
	case EndS:
		GameEnd();
		break;
	case StartS:
		GameStart();
		break;
	default:
		break;
	}

	//���Z�b�g����(�f�o�b�O�p)
	if (GetKeyState('R') & 0x80)
	{
		for (auto c : charList_)
		{
			c->Reset();
		}
		enemyList_.clear();
		charList_.clear();

		for (int i = 0; i < 4; i++)
		{
			charList_.push_back(player_[i]);
		}
		charList_.push_back(princess_);
		spawnManager_->Reset();

		princess_->SetSpawn(spawnManager_->GetSpawnList());
	}

	//camera_->Update(princess_->m_Pos);
}

//
//	@brief	�V�[���J�ڍX�V
SceneBase* Main_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	Update();

	if (GetKeyState(VK_F3) & 0x80)
	{
		next = new Title_Scene;
	}

	return next;
}

//
//	@brief	�Q�[���J�n
void Main_Scene::GameStart()
{
	//int count = 5;
	//if (++time_ % (FPS * count) == 0)
	//{
	//	scene_ = MainS;
	//}
	spawnFlg_ = false;
	if (GetKeyState(VK_RETURN) & 0x80)
	{
		scene_ = MainS;
		Sound::getInstance().BGM_play("SENTOU");

	}
}

//
//	@brief	�Q�[�����C��
void Main_Scene::GameMain()
{

	//�f�o�b�O�p
	if (GetKeyState('E') & 0x80)
	{
		scene_ = EndS;
	}
	if (GetKeyState('S') & 0x80)
	{
		spawnFlg_ = true;
	}

	////�G�l�~�[�X�|�[������
	if (spawnFlg_ == true)
	{
		if (enemyList_.size() < 50)
		{
			spawnManager_->Update(princess_);
			std::vector<EnemyJobManager*> temp = spawnManager_->OutEnemy();
			if (!temp.empty())
			{
				for (auto e : temp)
				{
					enemyList_.push_back(e);
					charList_.push_back(e);
				}
				temp.clear();
			}
		}


		//�G�l�~�[�^�[�Q�b�g�X�V
		if (!enemyList_.empty())
		{
			for (auto enemy : enemyList_)
			{
				//�v���C���[���[�v
				for (int i = 0; i < 4; i++)
				{
					enemy->Target_Update(player_[i], princess_);
				}
			}
		}
	}

	//�L�����X�V
	for (auto chara : charList_)
	{
		chara->CharaUpdate();
		chara->SetAllCharaList(charList_);
	}

	//�P�̖ړI�n�X�V
	D3DXVECTOR3 pos = princess_->m_Pos;
	CharaType no = PrincessT;
	double timing = 0;
	for (int i = 0; i < 4; i++)
	{
		if (timing < player_[i]->GetCallTiming())
		{
			timing = player_[i]->GetCallTiming();
			no = player_[i]->GetCharaType();
		}
	}
	if (no != PrincessT)
	{
		pos = player_[no]->GetCallPos();
	}

	princess_->SetDestination(pos);

	//�X�|�[���Q�[�g����
	spawnManager_->SealSpawn(princess_->SealSpawn());

	//�Փ˔���̍X�V
	CollisionControl();

	//�L�����̈ړ��X�V
	for (auto chara : charList_)
	{
		chara->Move_Update();
	}

	//�G�l�~�[���S�����X�V
	EnemyDestroy();

	//���S�v���C���[�X�V
	int deadCount = 0;
	for (int i = 0; i < 4; i++)
	{
		if (!player_[i]->GetAliveFlg())
		{
			princess_->SetDeadCharaList(player_[i]);
			++deadCount;
		}
	}

	//�Q�[���I��(�P���S ���� �v���C���[�S�� ���̓N���A)
	if (!(princess_->GetAliveFlg() || deadCount == 4))
	{
		scene_ = EndS;
	}
}

//
//	@brief	�Q�[���I��
void Main_Scene::GameEnd()
{
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		scene_ = StartS;

		princess_->SetSpawn(spawnManager_->GetSpawnList());

		for (auto c : charList_)
		{
			c->Reset();
		}
		enemyList_.clear();
		charList_.clear();

		for (int i = 0; i < 4; i++)
		{
			charList_.push_back(player_[i]);
		}
		charList_.push_back(princess_);
		spawnManager_->Reset();

		princess_->SetSpawn(spawnManager_->GetSpawnList());
	}
}

//
//	@brief	�G�l�~�[���S����
void Main_Scene::EnemyDestroy()
{
	if (!enemyList_.empty())
	{
		for (auto c : enemyList_)
		{
			if (!c->GetAliveFlg())
			{
				killList_.push_back(c);
			}
		}
	}

	if (!killList_.empty())
	{
		for (auto c : killList_)
		{
			//�L�������X�g����T��
			auto cl = std::find(std::begin(charList_), std::end(charList_), c);

			//�G�l�~�[���X�g����T��
			auto el = std::find(std::begin(enemyList_), std::end(enemyList_), c);

			//�@�I�u�W�F�N�g�̏I������
			delete (*cl);
			//	���X�g����O��
			charList_.erase(cl);
			enemyList_.erase(el);
		}
		killList_.clear();
	}
}

//
//	@brief	�Փ˔���Ǘ�
void Main_Scene::CollisionControl()
{

	//�����蔻��
	float fDistance = 0;
	D3DXVECTOR3 vNormal;

	//�ǂƂ̏Փ˔���
	//bool wallFlg = false;
	for (auto chara : charList_)
	{
		if (chara->m_Dir != D3DXVECTOR3(0, 0, 0))
		{
			if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
			{
				if (chara->GetKnockBackFlg() == true)
				{
					chara->SetKnockBackFlg(false);
				}

				//�������ԂȂ̂ŁA���点��
				chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
				//����x�N�g����̕ǂƂ̃��C���� �Q�d�ɔ���	
				if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
				{
					chara->StopMove();
				}
			}
		}

	}

	//���ӂɃL�����N�^�[�����邩�ǂ���
	for (int i = 0; i < charList_.size(); i++)
	{
		for (int j = i + 1; j < charList_.size(); j++)
		{
			if (ray_->CheckSpaceNo(charList_[i]->GetSpaceNo(), charList_[j]->GetSpaceNo()))
			{
				charList_[i]->SetAroundChara(charList_[j]);
				charList_[j]->SetAroundChara(charList_[i]);
			}
		}
	}
}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Main_Scene::Render(/*D3DXMATRIX mView, D3DXMATRIX mProj*/)
{

	//�X�e�[�W�̕`��
	stage_->Render();

	//�X�|�[���Q�[�g�̕`��
	spawnManager_->Render();

	for (auto chara : charList_)
	{
		chara->CharaRender();
	}

#ifdef _DEBUG
	PlayerDebug();
	//EnemyDebug();
#endif // _DEBUG

	camera_->Render();
}

void Main_Scene::PlayerDebug()
{
	//�f�o�b�O�`��
	char str[256];


#ifdef _DEBUG
	sprintf(str, "chara:%d", player_[Player1]->GetAroundC());
	debugText_->Render(str, 0, 50);
#endif // _DEBUG


	if (scene_ == MainS)
	{
		float high = 960;
		sprintf(str, "%f  %f  %f", player_[Player1]->m_Pos.x, player_[Player1]->m_Pos.y, player_[Player1]->m_Pos.z);
		debugText_->Render(str, 248, high);
		/*sprintf(str, "%d", player_[Player2]->m_Pos);
		debugText_->Render(str, 760, high);
		sprintf(str, "%d", player_[Player3]->m_Pos);
		debugText_->Render(str, 1240, high);
		sprintf(str, "%d", player_[Player4]->m_Pos);
		debugText_->Render(str, 1740, high);*/
	}


}

//void Main_Scene::EnemyDebug()
//{
//	char str[256];
//	if (!enemyList_.empty())
//	{
//		sprintf(str, "count:%d", enemyList_.size());
//		debugText_->Render(str, 0, 30);
//		
//	}
//}