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
	//uiClear_ = new TD_Graphics;
	//uiFailed_ = new TD_Graphics;
	for (int i = 0; i < UI_TIME; i++)
	{
		uiTime_[i] = new TD_Graphics;
	}
	//uiDebug_ = new TD_Graphics;
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
	//delete uiClear_;
	//uiClear_ = nullptr;
	//delete uiFailed_;
	//uiFailed_ = nullptr;

	for (int i = 0; i < UI_TIME; i++)
	{
		delete uiTime_[i];
		uiTime_[i] = nullptr;
	}
	//delete uiDebug_;
	//uiDebug_ = nullptr;
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
	Collision::StageSlideInit();


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
	//uiClear_->Init(L"./UI/UI_Tex/clear_font.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	//uiFailed_->Init(L"./UI/UI_Tex/failure_font.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	scale = D3DXVECTOR2(128, 256);
	float rect = 0.09;
	for (int i = 0; i < UI_TIME; i++)
	{
		uiTime_[i]->Init(L"./UI/UI_Tex/number.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f + i*rect, rect + i*rect));
	}
	//uiDebug_->Init(L"./UI/UI_Tex/number.png", D3DXVECTOR2(0, 0), scale, D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 0.1f));
	failedFlg_ = false;
	startCameraMovefirstFlg_ = true;
	startCameraMoveSecFlg_ = false;
	time_ = 0;
	scene_ = StartS;
	enemyCount_ = 0;

	Sound::getInstance().BGM_play("SENTOU");
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
	Sound::getInstance().BGM_stop("SENTOU");
	/*for (auto c : charList_)
	{
		c->Destroy();
	}*/
	charList_.clear();
	charList_.shrink_to_fit();
	//enemyList_.clear();
	player_.clear();
	//player_.shrink_to_fit();

	delete stage_;
	stage_ = nullptr;
	delete spawnManager_;
	spawnManager_ = nullptr;
	/*for (int i = 0; i < charList_.size(); i++)
	{
		charList_[i]->Destroy();
	}*/
}


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
			Result_Scene::clearFlg_ = true;
			next = new Result_Scene;
		}
		else
		{
			//next = new CharactorSelection_Scene;
			Result_Scene::clearFlg_ = false;
			next = new Result_Scene;
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
//#ifdef _DEBUG
	//���Z�b�g����(�f�o�b�O�p)
	if (GetKeyState('R') & 0x80)
	{
		for (auto c : charList_)
		{
			c->Reset();
		}
		//enemyList_.clear();
		charList_.clear();

		for (int i = 0; i < 4; i++)
		{
			charList_.push_back(player_[i]);
		}
		charList_.push_back(princess_);
		spawnManager_->Reset();

		princess_->SetSpawn(spawnManager_->GetSpawnList());
	}
	if (GetKeyState('C')&0x80)
	{
		scene_ = EndS;
	}
	if (GetKeyState('F') & 0x80)
	{
		failedFlg_ = true;
		scene_ = EndS;
	}
//#endif
	//camera_->Update(princess_->m_Pos);
}


//
//	@brief	�Q�[���J�n
void Main_Scene::GameStart()
{
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

	//�J�����ړ�
	camera_->gazePoint_ = princess_->m_Pos;
	for (int i=0;i<4;i++)
	{
		camera_->SetPlayerPos(player_[i]->m_Pos,i);
	}
	camera_->Main_Game_Update();

	//if (enemyList_.size() < 50)
	if (enemyCount_ < ENEMY_MAX)
	{
		spawnManager_->Update(princess_);
		std::vector<EnemyJobManager*> temp = spawnManager_->OutEnemy();
		if (!temp.empty())
		{
			for (auto e : temp)
			{
				++enemyCount_;
				//enemyList_.push_back(e);
				charList_.push_back(e);
			}
			temp.clear();
		}
	}

	//���݂��Ă��邷�ׂẴL�����N�^�[�Z�b�g
	CharactorManager::allCharaList_ = charList_;

	//�G�l�~�[�A�v���C���[�ƕP���̍X�V
	EnemyManager::princess_ = princess_;
	EnemyManager::playerList_ = player_;

	////��Ԕԍ��̃��Z�b�g�ƍX�V
	//Collision::StageSpaceReset();
	//for (auto chara : charList_)
	//{
	//	Collision::SetSpaceNoArray(chara->m_Pos);
	//}

	//�L�����X�V
	for (auto chara : charList_)
	{
		start1 = timeGetTime();
		chara->CharaUpdate();
		end1 = timeGetTime();
		result1 = end1 - start1;

		if (chara->GetCharaType() == Enemy && !chara->GetAliveFlg())
		{
			killList_.push_back(chara);
		}
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
		if (!player_[i]->GetAliveFlg() && !player_[i]->GetRevivalFlg())
		{
			princess_->SetDeadCharaList(player_[i]);
			++deadCount;
		}
	}

	//�Q�[���I��
	//�P���S ���� �v���C���[�S��
	if (!princess_->GetAliveFlg() || deadCount == 4)
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
	//���[�V�����Z�b�g
	if (failedFlg_)
	{
		princess_->DeadMotion();
		Sound::getInstance().BGM_stop("SENTOU");
	}
	for (auto p : player_)
	{
		p->SetEndMotion(failedFlg_);
		GamePad::stopVibration(p->GetCharaType());
	}

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
		//enemyList_.clear();
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
	/*if (!enemyList_.empty())
	{
		for (auto c : enemyList_)
		{
			if (!c->GetAliveFlg())
			{
				killList_.push_back(c);
			}
		}
	}*/

	if (!killList_.empty())
	{
		for (auto c : killList_)
		{
			//�L�������X�g����T��
			auto cl = std::find(std::begin(charList_), std::end(charList_), c);

			////�G�l�~�[���X�g����T��
			//auto el = std::find(std::begin(enemyList_), std::end(enemyList_), c);

			//�@�I�u�W�F�N�g�̏I������
			delete (*cl);
			//	���X�g����O��
			charList_.erase(cl);
			--enemyCount_;
			//enemyList_.erase(el);
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
		start2 = timeGetTime();
		if (chara->m_Dir != D3DXVECTOR3(0, 0, 0))
		{
			if (ray_->RayIntersect(chara->m_Pos, chara->m_Dir, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
			{
				if (chara->GetKnockBackFlg() == true)
				{
					chara->SetKnockBackFlg(false);
				}
				chara->StopMove();
				//�������ԂȂ̂ŁA���点��
				chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
				//����x�N�g����̕ǂƂ̃��C���� �Q�d�ɔ���	
				if (ray_->RayIntersect(chara->m_Pos, chara->m_Dir, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
				{
					chara->StopMove();
				}
			}
		}
		end2 = timeGetTime();
		result2 = end2 - start2;
	}

	//���ӂɃL�����N�^�[�����邩�ǂ���
	for (int i = 0; i < charList_.size(); i++)
	{
		for (int j = i + 1; j < charList_.size(); j++)
		{
			if (ray_->CheckSpaceNo(charList_[i]->GetSpaceNo(), charList_[j]->GetSpaceNo(), 1,2))
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

	//�X�e�[�W�̕`��
	stage_->Render();

	//�L�����`��
	for (auto chara : charList_)
	{
		chara->CharaRender();
	}

	//�X�|�[���Q�[�g�̕`��
	spawnManager_->Render();

	//�G�t�F�N�g�̍X�V�ƕ`��
	Effect::getInstance().SetCamera(camera_->movePow_, camera_->gazePoint_);
	Effect::getInstance().Update();
	Effect::getInstance().Draw();

	//UI�`��
	//if (scene_ == MainS)
	//{
	//���ԕ`��
	float posX = 1400;
	float space = 80;
	D3DXVECTOR2 scale(0.5, 0.5);
	//��
	int minutes10 = time_ / (FPS*FPS * 10) % 6;// time_ / FPS % 6;
	int minutes1 = time_ / (FPS*FPS) % 10;// time_ / FPS;
	uiTime_[minutes10]->Render(D3DXVECTOR2(posX, 0), scale, true);
	uiTime_[minutes1]->Render(D3DXVECTOR2(posX + space * 0.8, 0), scale, true);
	uiTime_[SEMICOLON]->Render(D3DXVECTOR2(posX + space * 1.33, 0), scale, true);
	//�b
	int second10 = time_ / (FPS * 10) % 6;
	int second1 = time_ / FPS % 10;
	uiTime_[second10]->Render(D3DXVECTOR2(posX + space * 2, 0), scale, true);
	uiTime_[second1]->Render(D3DXVECTOR2(posX + space * 2.8, 0), scale, true);
	uiTime_[SEMICOLON]->Render(D3DXVECTOR2(posX + space * 3.3, 0), scale, true);
	//�~���b
	int conma10 = time_ / 10 % 6;
	int conma1 = time_ % 10;
	uiTime_[conma10]->Render(D3DXVECTOR2(posX + space * 4, 0), scale, true);
	uiTime_[conma1]->Render(D3DXVECTOR2(posX + space * 4.8, 0), scale, true);

	float posY = 380;
	posX = 180;
	if (scene_ == StartS && startCameraMoveSecFlg_)
	{
		//static float posX = 180;
		uiStart_->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(1, 1), true);
	}
	else if (scene_ == EndS && !failedFlg_)
	{
		Result_Scene::m10_Time = minutes10;
		Result_Scene::m1_Time = minutes1;
		Result_Scene::s10_Time = second10;
		Result_Scene::s1_Time = second1;
		Result_Scene::c10_Time = conma10;
		Result_Scene::c1_Time = conma1;

		//uiFailed_->Render(D3DXVECTOR2(posX, posY), D3DXVECTOR2(1, 1), true);
	}


	/*Result_Scene::m10_Time = minutes10;
	Result_Scene::m1_Time = minutes1;
	Result_Scene::s10_Time = second10;
	Result_Scene::s1_Time = second1;
	Result_Scene::c10_Time = conma10;
	Result_Scene::c1_Time = conma1;*/

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
	sprintf(str, "pos.x:%f pos.y:%f pos.z:%f",camera_->movePow_.x,camera_->movePow_.y,camera_->movePow_.z);
	debugText_->Render(str, 0, 50);
	sprintf(str, "dist:%f", camera_->dist_[Player1]);
	debugText_->Render(str, 0, 80);

	//sprintf(str, "enemy:%d", enemyCount_);
	//debugText_->Render(str, 0, 50);
	//sprintf(str, "allchara:%d", charList_.size());
	//debugText_->Render(str, 0, 80);
	//sprintf(str, "aroundChara:%d", player_[Player1]->GetAroundC());
	//debugText_->Render(str, 0, 110);
	//Collision* col = new Collision;
	//int no = col->SetSpaceNo(player_[Player1]->m_Pos, 1);
	//sprintf(str, "spaceNo:%d", no);
	//debugText_->Render(str, 0, 140);
	//sprintf(str, "spaceNo:%d", player_[Player1]->GetSpaceNo());
	//debugText_->Render(str, 0, 170);


	//if (scene_ == MainS)
	//{
	//	if (!enemyList_.empty())
	//	{
	//		float temp = 0;
	//		for (auto e : enemyList_)
	//		{
	//			float high = 300+temp;
	//			sprintf(str, "motionNo_ : %d", e->GetMotionNo());
	//			debugText_->Render(str, 0, high);
	//			temp += 30;
	//		}

	//	}
	//	/*sprintf(str, "%d", player_[Player2]->m_Pos);
	//	debugText_->Render(str, 760, high);
	//	sprintf(str, "%d", player_[Player3]->m_Pos);
	//	debugText_->Render(str, 1240, high);
	//	sprintf(str, "%d", player_[Player4]->m_Pos);
	//	debugText_->Render(str, 1740, high);*/
	//}


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