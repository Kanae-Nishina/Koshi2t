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
	camera_ = new Camera;
	debugText_ = new D3D11_TEXT;
	creator_ = new CharactorCreator;
	uiStart_ = new TD_Graphics;
	uiClear_ = new TD_Graphics;
	uiFailed_ = new TD_Graphics;
	for (int i = 0; i < UI_TIME; i++)
	{
		uiTime_[i] = new TD_Graphics;
	}
	uiDebug_ = new TD_Graphics;
}

//
//	@brief	�f�X�g���N�^
Main_Scene::~Main_Scene()
{
	delete camera_;
	camera_ = nullptr;
	delete creator_;
	creator_ = nullptr;
	delete uiStart_;
	uiStart_ = nullptr;
	delete uiClear_;
	uiClear_ = nullptr;
	delete uiFailed_;
	uiFailed_ = nullptr;

	for (int i = 0; i < UI_TIME; i++)
	{
		delete uiTime_[i];
		uiTime_[i] = nullptr;
	}
	delete uiDebug_;
	uiDebug_ = nullptr;
}

//
//	@brief	������
void Main_Scene::Init()
{
	creator_->LoadData();
	//camera_->movePow_ = D3DXVECTOR3(0, 45, -45);
	//camera_->gazePoint_ = D3DXVECTOR3(0, 0, -12);
	camera_->movePow_ = D3DXVECTOR3(-3, 1, -15);
	//camera_->gazePoint_ = D3DXVECTOR3(-3, 0, -10);

	stage_ = new Stage;
	spawnManager_ = new SpawnManager;
	stage_->Init("�X�e�[�W5");
	spawnManager_->Init("�X�|�[��");


	JobManager* ply;
	for (int i = 0; i < 4; i++)
	{
		player_.push_back(ply);
	}
	player_[Player1] = SetCharaJob(CharactorCreator::player1_, Player1);
	player_[Player1]->CharaInit(CharactorCreator::player1_);
	player_[Player1]->m_Pos = D3DXVECTOR3(-3, 0, -10);
	player_[Player2] = SetCharaJob(CharactorCreator::player2_, Player2);
	player_[Player2]->CharaInit(CharactorCreator::player2_);
	player_[Player2]->m_Pos = D3DXVECTOR3(-1.5, 0, -10);
	player_[Player3] = SetCharaJob(CharactorCreator::player3_, Player3);
	player_[Player3]->CharaInit(CharactorCreator::player3_);
	player_[Player3]->m_Pos = D3DXVECTOR3(1.5, 0, -10);
	player_[Player4] = SetCharaJob(CharactorCreator::player4_, Player4);
	player_[Player4]->CharaInit(CharactorCreator::player4_);
	player_[Player4]->m_Pos = D3DXVECTOR3(3, 0, -10);

	princess_ = new Princess;
	princess_->CharaInit("�P");
	princess_->m_Pos = D3DXVECTOR3(0, 0, -12);
	princess_->m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
	princess_->SetSpawn(spawnManager_->GetSpawnList());

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(player_[i]);
	}
	charList_.push_back(princess_);

	//UI
	D3DXVECTOR2 scale(1623, 336);
	uiStart_->Init(L"./UI/UI_Tex/start_font.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	uiClear_->Init(L"./UI/UI_Tex/clear_font.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	uiFailed_->Init(L"./UI/UI_Tex/failure_font.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	scale = D3DXVECTOR2(128, 256);
	float rect = 0.083;
	for (int i = 0; i < UI_TIME; i++)
	{
		uiTime_[i]->Init(L"./UI/UI_Tex/number.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f + i*rect, rect + i*rect));
	}
	uiDebug_->Init(L"./UI/UI_Tex/number.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 0.1f));
	failedFlg_ = false;
	startCameraMovefirstFlg_ = true;
	startCameraMoveSecFlg_ = false;
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
	charList_.clear();
	enemyList_.clear();
	player_.clear();
	/*for (int i = 0; i < charList_.size(); i++)
	{
		charList_[i]->Destroy();
	}*/
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
//	@brief	�V�[���J�ڍX�V
SceneBase* Main_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	Update();

	if (scene_ == NextS)
	{
		if (!failedFlg_)
		{
			next = new Result_Scene;
		}
		else
		{
			next = new Title_Scene;
		}
	}

	return next;
}

//
//	@brief	�X�V
void Main_Scene::Update()
{
	switch (scene_)
	{
	case MainS:
		GameMain();
		camera_->gazePoint_ = princess_->m_Pos;
		camera_->Main_Game_Update();
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
//	@brief	�Q�[���J�n
void Main_Scene::GameStart()
{
	Sound::getInstance().BGM_play("SENTOU");
	if (startCameraMovefirstFlg_)
	{
		startCameraMoveSecFlg_ = camera_->Main_Start_FirstUpdate();
	}
	bool next = false;
	if (startCameraMoveSecFlg_)
	{
		startCameraMovefirstFlg_ = false;
		next = camera_->Main_Start_SecondUpdate();
	}

	if (next)
	{
		scene_ = MainS;
	}
}

//
//	@brief	�Q�[�����C��
void Main_Scene::GameMain()
{
	//���ԃJ�E���g
	++time_;

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

	//���݂��Ă��邷�ׂẴL�����N�^�[�Z�b�g
	CharactorManager::allCharaList_ = charList_;


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
	//}

	//�L�����X�V
	for (auto chara : charList_)
	{
		chara->CharaUpdate();
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

	//�Q�[���I��
	//�P���S ���� �v���C���[�S��
	if (!(princess_->GetAliveFlg() || deadCount == 4))
	{
		failedFlg_ = true;
		scene_ = EndS;
	}
	//�X�|�[���Q�[�g���ׂĔj��
	if (spawnManager_->GetSpawnList().empty())
	{
		scene_ = EndS;
	}
}

//
//	@brief	�Q�[���I��
void Main_Scene::GameEnd()
{
	static int endCount = 0;
	if (++endCount % (FPS * 5) == 0)
	{
		scene_ = NextS;
	}

#ifdef _DEBUG
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
#endif //_DEBUG
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
void Main_Scene::Render()
{
	//�X�|�[���Q�[�g�̕`��
	spawnManager_->Render();

	//�X�e�[�W�̕`��
	stage_->Render();

	//�L�����`��
	for (auto chara : charList_)
	{
		chara->CharaRender();
	}


	//UI�`��
	//if (scene_ == MainS)
	//{
	//���ԕ`��
	float posX = 1400;
	float space = 80;
	D3DXVECTOR2 scale(0.5,0.5);
	//��
	int minutes10 = time_ / (FPS*FPS * 10) % 6;// time_ / FPS % 6;
	int minutes1 = time_ / (FPS*FPS) % 10;// time_ / FPS;
	uiTime_[minutes10]->Render(D3DXVECTOR2(posX, 0),scale, true);
	uiTime_[minutes1]->Render(D3DXVECTOR2(posX + space * 1, 0),scale, true);
	uiTime_[SEMICOLON]->Render(D3DXVECTOR2(posX + space * 1.5, 0),scale, true);
	//�b
	int second10 = time_ / (FPS * 10) % 6;
	int second1 = time_ / FPS % 10;
	uiTime_[second10]->Render(D3DXVECTOR2(posX + space * 2, 0),scale, true);
	uiTime_[second1]->Render(D3DXVECTOR2(posX + space * 3, 0),scale, true);
	uiTime_[SEMICOLON]->Render(D3DXVECTOR2(posX + space * 3.5, 0),scale, true);
	//�~���b
	int conma10 = time_ / 10 % 6;
	int conma1 = time_ % 10;
	uiTime_[conma10]->Render(D3DXVECTOR2(posX + space * 4, 0),scale, true);
	uiTime_[conma1]->Render(D3DXVECTOR2(posX + space * 5, 0),scale, true);

	float posY = 380;
	posX = 180;
	if (scene_ == StartS && startCameraMoveSecFlg_)
	{
		//static float posX = 180;
		uiStart_->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(1, 1), true);
	}
	else if (scene_ == EndS && failedFlg_)
	{
		uiFailed_->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(1, 1), true);
	}


	////�f�o�b�O�`��
	//char str[256];
	//sprintf(str, "%d", second1);
	//debugText_->Render(str, 0, 50);
	//sprintf(str, "%d", second10);
	//debugText_->Render(str, 0, 80);

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


	//sprintf(str, "chara:%d", player_[Player1]->GetAroundC());
	//debugText_->Render(str, 0, 50);



	if (scene_ == MainS)
	{
		float high = 300;
		sprintf(str, "m_no%d", player_[Player1]->GetMotionNo());
		debugText_->Render(str, 0, high);
		sprintf(str, "atk_no%d", player_[Player1]->GetAtkState());
		debugText_->Render(str, 0, high+30);

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