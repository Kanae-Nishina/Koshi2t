//
//	@file	Main_Scene.cpp
//	@brief	�Q�[�����C���V�[���Ǘ�
//	@date	2016/11/08
//	@outher	�m�ȍ��c

#include "./Main_Scene.h"

//
//	@brief	�R���X�g���N�^
Main_Scene::Main_Scene()
{
	stage_ = new Stage;
	//virChar_ = new JobManager *[4];
	JobManager* ply;
	for (int i = 0; i < 4; i++)
	{
		virChar_.push_back(ply);
	}

	virChar_[Player1] = new SwordMan(Player1);
	virChar_[Player2] = new ShieldMan(Player2);
	virChar_[Player3] = new Witch(Player3);
	virChar_[Player4] = new Bomber(Player4);
	princess_ = new Princess;

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(virChar_[i]);
	}
	charList_.push_back(princess_);
	scene_ = StartS;

	slime_ = new CD3DXSKINMESH;
	//virEnemy_ = new Slim;

	camera_ = new Camera;
}

//
//	@brief	�f�X�g���N�^
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	if (spawn_ != nullptr)
	{
		SAFE_DELETE(spawn_);
		//delete spawn_;
		//spawn_ = nullptr;
	}

	//delete ray_;
	//ray_ = nullptr;

	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(virChar_[i]);
		//delete virChar_[i];
		//virChar_[i] = nullptr;
	}
	//delete[] virChar_;
	//virChar_ = nullptr;


	SAFE_DELETE(princess_);
	//delete princess_;
	//princess_ = nullptr;


	//for (auto chara : charList_)
	//{
	//	delete chara;
	//	chara = nullptr;
	//}
	//for (int i = 0; i < 10; i++)
	//{
	//delete virEnemy_;
	//virEnemy_ = nullptr;
	//}
	SAFE_DELETE(virEnemy_);
	//delete virEnemy_;
	//virEnemy_ = nullptr;

	SAFE_DELETE(slime_);
	//delete slime_;
	//slime_ = nullptr;

	delete debugText_;
	debugText_ = nullptr;

	delete xfile;
	xfile = nullptr;
	delete parameter;
	parameter = nullptr;

	delete camera_;
	camera_ = nullptr;


	delete uisword_;
	uisword_ = nullptr;
	delete uiseeld_;
	uiseeld_ = nullptr;
	delete uimagic_;
	uimagic_ = nullptr;
	delete uibom_;
	uibom_ = nullptr;
}

//
//	@brief						������
//	@param (m_hWnd)				�E�B���h�E�̃n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
void Main_Scene::Init(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext)
{
	wnd_ = m_hWnd;
	device_ = m_pDevice;
	//deviceContext_ = m_pDeviceContext;
	//
	////Direct3D�ƃV�F�[�_�[�̏�����
	//STATICMESH::CD3DXMESH::InitDx9();

	//�ǂݍ���X�t�@�C���̏���ǂݍ���
	xfileRead = new XFileRead;
	xfileRead->ReadXFilePath();

	//�ǂݍ��݃p�����[�^�f�[�^�̏���ǂݍ���
	parameter = new ParameterRead;
	parameter->SetJobParameter("./ReadData/JobParameterData.csv");
	//JobParameter* job = parameter->GetJobParamList("���m");

	//���[�V�����f�[�^�̓ǂݍ���
	motionRead_ = new MotionRead;
	motionRead_->PlayerMotionRead();

	//�X�e�[�W�̃t�@�C���ǂݍ���
	xfile = xfileRead->GetXFile("�X�e�[�W5");
	stage_->Read(xfile->GetFileName());

	//�X�|�[���̐ݒ�
	xfile = xfileRead->GetXFile("�X�|�[��1");
	spawnAmount_ = 1;
	spawn_ = new Spawn;
	spawn_->SpawnInit(xfile->GetFileName());

	//���L�����t�@�C���ǂݍ���
	char name[80];
	memset(name, 0, sizeof(name));
	xfile = xfileRead->GetXFile("���m");
	memcpy(name, virChar_[Player1]->CharaInit(xfile->GetFileName()), sizeof(name));
	virChar_[Player1]->CreateFromX(name);
	virChar_[Player1]->SetParameter(parameter->GetJobParamList("���m"));
	virChar_[Player1]->SetMotionData(motionRead_->GetMotionUser("���m"));
	virChar_[Player1]->m_Pos = D3DXVECTOR3(-3, 0, -10);

	char name2[80];
	memset(name2, 0, sizeof(name2));
	xfile = xfileRead->GetXFile("���m");
	memcpy(name2, virChar_[Player2]->CharaInit(xfile->GetFileName()), sizeof(name2));
	virChar_[Player2]->CreateFromX(name2);
	//virChar_[Player2]->CharaInit(xfile->GetFileName());
	virChar_[Player2]->SetParameter(parameter->GetJobParamList("���m"));
	virChar_[Player2]->SetMotionData(motionRead_->GetMotionUser("���m"));
	virChar_[Player2]->m_Pos = D3DXVECTOR3(-1.5, 0, -10);

	char name3[80];
	memset(name3, 0, sizeof(name3));
	xfile = xfileRead->GetXFile("�����m");
	memcpy(name3, virChar_[Player3]->CharaInit(xfile->GetFileName()), sizeof(name3));
	virChar_[Player3]->CreateFromX(name3);
	//virChar_[Player3]->CharaInit(xfile->GetFileName());
	virChar_[Player3]->SetParameter(parameter->GetJobParamList("�����m"));
	virChar_[Player3]->SetMotionData(motionRead_->GetMotionUser("�����m"));
	virChar_[Player3]->m_Pos = D3DXVECTOR3(1.5, 0, -10);

	char name4[80];
	memset(name4, 0, sizeof(name4));
	xfile = xfileRead->GetXFile("���e�m");
	memcpy(name4, virChar_[Player4]->CharaInit(xfile->GetFileName()), sizeof(name4));
	virChar_[Player4]->CreateFromX(name4);
	//virChar_[Player4]->CharaInit(xfile->GetFileName());
	virChar_[Player4]->SetParameter(parameter->GetJobParamList("���e�m"));
	virChar_[Player4]->SetMotionData(motionRead_->GetMotionUser("���e�m"));
	virChar_[Player4]->m_Pos = D3DXVECTOR3(3, 0, -10);

	char name5[80];
	memset(name5, 0, sizeof(name5));
	xfile = xfileRead->GetXFile("�P");
	memcpy(name5, princess_->CharaInit(xfile->GetFileName()), sizeof(name5));
	princess_->CreateFromX(name5);
	//princess_->CharaInit(xfile->GetFileName());
	princess_->SetMotionData(motionRead_->GetMotionUser("�P"));
	princess_->m_Pos = D3DXVECTOR3(0, 0, -12);
	princess_->SetSpawn(spawn_);



	//�G�l�~�[�̓ǂݍ���
	parameter->SetEnemyParameter("./ReadData/EnemyParameterData.csv");

	char name6[80];
	memset(name6, 0, sizeof(name6));
	xfile = xfileRead->GetXFile("�X���C��");
	virEnemy_ = new Slim;
	memcpy(name6, virEnemy_->CharaInit(xfile->GetFileName()), sizeof(name6));
	slime_->CreateFromX(name6);
	//virEnemy_->CharaInit(name);
	time_ = 0;

	EffectInit(m_pDeviceContext);

	//�f�[�^�̉��
	/*delete xfile;
	xfile = nullptr;
	delete parameter;
	parameter = nullptr;*/

}

//
//	@brief	�f�o�b�O�p������
HRESULT Main_Scene::DebugInit(ID3D11DeviceContext* m_pDeviceContext)
{
	debugText_ = new D3D11_TEXT;
	deviceContext_ = m_pDeviceContext;
	D3DXVECTOR4 vColor(0, 0, 0, 1);
	if (FAILED(debugText_->Init(deviceContext_, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Main_Scene::EffectInit(ID3D11DeviceContext* m_pDeviceContext)
{
	uisword_ = new D3D11_SPRITE;
	deviceContext_ = m_pDeviceContext;
	float scaleF = 7;
	D3DXVECTOR3 scale(scaleF, scaleF, scaleF);
	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
	if (FAILED(uisword_->CreateEffects(L"./Effect/Effect_Tex/UISword.png", true, D3DXVECTOR2(1, 1), 5, scale)))
	{
		return E_FAIL;
	}
	uiseeld_ = new D3D11_SPRITE;
	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
	if (FAILED(uiseeld_->CreateEffects(L"./Effect/Effect_Tex/UISeeld.png", true, D3DXVECTOR2(1, 1), 5, scale)))
	{
		return E_FAIL;
	}
	uimagic_ = new D3D11_SPRITE;
	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
	if (FAILED(uimagic_->CreateEffects(L"./Effect/Effect_Tex/UIMagic.png", true, D3DXVECTOR2(1, 1), 5, scale)))
	{
		return E_FAIL;
	}
	uibom_ = new D3D11_SPRITE;
	//�p�X�A���߃t���O�A���N�g�T�C�Y�A�X�s�[�h�A�X�P�[���i���{�j	
	if (FAILED(uibom_->CreateEffects(L"./Effect/Effect_Tex/UIBom.png", true, D3DXVECTOR2(1, 1), 5, scale)))
	{
		return E_FAIL;
	}
	return S_OK;
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

	//�J�����̍X�V
	for (int i = 0; i < 4; i++)
	{
		camera_->SetPlayerPos(virChar_[i]->m_Pos);
	}
	camera_->Update();
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

	if (GetKeyState(VK_RETURN) & 0x80)
	{
		scene_ = MainS;
	}
}

//
//	@brief	�Q�[�����C��
void Main_Scene::GameMain()
{
	//�G�l�~�[�X�|�[������
	if (++time_ % (FPS * 5) == 0 && spawn_ != nullptr)
	{
		spawn_->ListSet(parameter, princess_);
		std::vector<EnemyJobManager*> temp = spawn_->EnemySpawn();
		for (auto e : temp)
		{
			//e->SetTarget(princess_);
			enemyList_.push_back(e);
			charList_.push_back(e);
		}
		spawn_->ListReset();
		temp.clear();
	}



	//�G�l�~�[�^�[�Q�b�g�X�V
	if (!enemyList_.empty())
	{
		for (auto enemy : enemyList_)
		{
			//�v���C���[���[�v
			for (int i = 0; i < 4; i++)
			{
				//�v���C���[�ƃG�l�~�[�����̋�����
				//float dist = 5.0;
				//if (ray_->CharaNear(enemy->m_Pos, virChar_[i]->m_Pos, dist))
				//{
				enemy->Target_Update(virChar_[i], princess_);
				//}
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
		if (timing < virChar_[i]->GetCallTiming())
		{
			timing = virChar_[i]->GetCallTiming();
			no = virChar_[i]->GetCharaType();
		}
	}
	if (no != PrincessT)
	{
		pos = virChar_[no]->GetCallPos();
	}

	princess_->SetDestination(pos);

	if (princess_->SealSpawn() != nullptr)
	{
		delete spawn_;
		spawn_ = nullptr;
	}


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
		if (!virChar_[i]->GetAliveFlg())
		{
			princess_->SetDeadCharaList(virChar_[i]);
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

			//�@�I�u�W�F�N�g�̏I������
			//delete (*el);
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
		if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
		{
			//�������ԂȂ̂ŁA���点��
			//virChar_[player1]->m_Pos = ray_->Slip(virChar_[player1]->m_Dir, vNormal);//����x�N�g�����v�Z
			chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
			//����x�N�g����̕ǂƂ̃��C���� �Q�d�ɔ���	
			if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
			{
				//virChar_[player1]->m_Pos = D3DXVECTOR3(0, 0, 0);//�~�߂�
				chara->StopMove();
				//wallFlg = true;
			}
		}


		////���ӂɃL�����N�^�[�����邩�ǂ����̊m�F
		//for (auto opp : charList_)
		//{
		//	if (chara != opp)
		//	{
		//		//chara��opp�̋����𔻒�

		//		//�߂�������
		//		chara->SetAroundChara(opp);
		//		opp->SetAroundChara(chara);
		//	}
		//}
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
	//D3DXMATRIX mView = camera_->GetView();
	//D3DXMATRIX mProj = camera_->GetProj();

	//virEnemy_->Render(D3DXVECTOR3(0, 0, 0));
	//virEnemy_->Render(D3DXVECTOR3(1, 0, 0));

	//�X�e�[�W�̕`��
	stage_->Render();

	EffectRender();

	//virEnemy_->CharaRender(mView, mProj);

	//���L�����`��
	/*for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaRender(mView, mProj);
	}*/

	if (!enemyList_.empty())
	{
		for (auto enemy : enemyList_)
		{
			slime_->Render(enemy->m_Pos, enemy->m_Yaw, enemy->m_Scale);
		}
	}

	for (auto chara : charList_)
	{
		if (chara->GetCharaType() != Enemy)
		{
			chara->CharaRender();
		}
	}

	if (spawn_ != nullptr)
	{
		//for (int i = 0; i < spawnAmount_; i++)
		//{
		if (spawn_ != nullptr)
		{
			spawn_->SpawnRender();
		}
		//}
	}

	PlayerDebug();
	EnemyDebug();

	camera_->Render();

	//char str[256];
	//sprintf(str, "%f",camera_->GetDist());
	//debugText_->Render(str, 0, 10);
	//sprintf(str, "zoom : %f", virChar_[Player2]->m_Pos.x);
	//debugText_->Render(str, 0, 30);
	//sprintf(str, "y : %f",camera_->GetPos().y);
	//debugText_->Render(str, 0, 50);
}

void Main_Scene::EffectRender()
{
	static float x = 0;
	D3DXMATRIX Tran, World, World2;
	//�r���{�[�h�̃��[���h�g�����X�t�H�[��	
	x = 0;
	D3DXMatrixTranslation(&Tran, x, 0, 0);
	World = Tran;
	World2 = Tran;
	D3DXMATRIX CancelRotation = Camera::mView_;
	CancelRotation._41 = CancelRotation._42 = CancelRotation._43 = 0;
	D3DXMatrixInverse(&CancelRotation, NULL, &CancelRotation);
	World2 = CancelRotation * World2;
	uisword_->RenderSprite(World2, D3DXVECTOR3(-20, 0, -25));
	uiseeld_->RenderSprite(World2, D3DXVECTOR3(-10, 0, -25));
	uimagic_->RenderSprite(World2, D3DXVECTOR3(0, 0, -25));
	uibom_->RenderSprite(World2, D3DXVECTOR3(10, 0, -25));
	//uisword_->RenderSprite(World*mView*mProj);	
	/*uisword_->RenderSprite(mView, mProj, virChar_[player1]->m_vPos.x, virChar_[player1]->m_vPos.y, virChar_[player1]->m_vPos.z);*/
	//float xaaaa = hikari_->m_vSize.x / 2;// hikari_->m_dwWindowWidth / 2 * hikari_->m_vSize.x;	
	//float y = 0;// hikari_->m_vSize.y / 2;	
	//float z = 0;// hikari_->m_vSize.y / 2;// hikari_->m_vSize.y;	
	//	//hikari_->m_fYaw = D3DXToRadian(-90);	
	//if (GamePad::checkInput(player1, GamePad::InputName::A) && flg == false)	
	//{	
	//	if (hikari_->m_isActive)	
	//	{	
	//	hikari_->RenderSprite(World2, mView, mProj, virEnemy_[0]->m_vPos.x - xaaaa/* - 3.55*/, (virEnemy_[0]->m_vPos.y + y), virEnemy_[0]->m_vPos.z - z /*- 0.5*//*virChar_[player1]->m_vPos.z-z*/);	
	//	}	
	//	else	
	//	{	
	//	hikari_->m_isActive = true;	
	//	hikari_->TexScroll = D3DXVECTOR4(0, 0, 0, 0);	
	//	hikari_->m_iAnimCount = 0;	
	//	}	
	//}	
}

void Main_Scene::PlayerDebug()
{
	//�f�o�b�O�`��
	char str[256];
	sprintf(str, "spaceNo %d", virChar_[Player1]->GetSpaceNo());
	debugText_->Render(str,0 , 10);
	sprintf(str, "%d", virChar_[Player1]->GetHP());
	debugText_->Render(str, 370, 952);
	sprintf(str, "%d", virChar_[Player2]->GetHP());
	debugText_->Render(str, 775, 952);
	sprintf(str, "%d", virChar_[Player3]->GetHP());
	debugText_->Render(str, 1195, 952);
	sprintf(str, "%d", virChar_[Player4]->GetHP());
	debugText_->Render(str, 1620, 952);
	//sprintf(str, "Atk(no0,w1,na2,c3,sa4) : %d", virChar_[Player2]->GetAtkState());
	//debugText_->Render(str, 0, 10);
	////sprintf(str, "alive : %d", virChar_[Player2]->GetAliveFlg());
	////debugText_->Render(str, 0, 10);
	//sprintf(str, "motionNo : %d", virChar_[Player2]->GetMotionNo());
	//debugText_->Render(str, 0, 30);
	//sprintf(str, "motionSPeed : %f", virChar_[Player2]->GetMotionSpeed());
	//debugText_->Render(str, 0, 50);
	//sprintf(str, "motionCount : %d", virChar_[Player2]->GetMotionCount());
	//debugText_->Render(str, 0, 70);
	//sprintf(str, "def_ : %d", virChar_[Player2]->GetParam()->def_);
	//debugText_->Render(str, 0, 90);
	//sprintf(str, "specialAttackTime_ : %f", virChar_[Player2]->GetParam()->specialAttackTime_);
	//debugText_->Render(str, 0, 110);
	//sprintf(str, "chargeTime_ : %d", virChar_[Player2]->GetParam()->chargeTime_);
	//debugText_->Render(str, 0, 130);
	//sprintf(str, "moveSpeed_ : %f", virChar_[Player2]->GetParam()->moveSpeed_);
	//debugText_->Render(str, 0, 150);
	//sprintf(str, "specialMoveSpeed_ : %f", virChar_[Player2]->GetParam()->specialMoveSpeed_);
	//debugText_->Render(str, 0, 170);
	//sprintf(str, "weight_ : %f", virChar_[Player2]->GetParam()->weight_);
	//debugText_->Render(str, 0, 190);
	//sprintf(str, "attackReach_ : %f", virChar_[Player2]->GetParam()->attackReach_);
	//debugText_->Render(str, 0, 210);
	//sprintf(str, "attackRange_ : %f", virChar_[Player2]->GetParam()->attackRange_);
	//debugText_->Render(str, 0, 230);
	//sprintf(str, "scale_ : %f", virChar_[Player2]->GetParam()->scale_);
	//debugText_->Render(str, 0, 250);
	//sprintf(str, "x : %f y :%f", virChar_[Player2]->m_Pos.x, virChar_[Player2]->m_Pos.z);
	//debugText_->Render(str, 0, 270);
}

void Main_Scene::EnemyDebug()
{
	char str[256];
	if (!enemyList_.empty())
	{
		//EnemyJobManager* obj = enemyList_[0];
		sprintf(str, "count : %d", enemyList_.size());
		debugText_->Render(str, 0, 30);
		/*sprintf(str, "alive : %d", obj->GetAliveFlg());
		debugText_->Render(str, 0, 10);
		sprintf(str, "hp_ : %d", obj->GetHP());
		debugText_->Render(str, 0, 30);
		sprintf(str, "atk_ : %d", obj->GetParam()->atk_);
		debugText_->Render(str, 0, 50);
		sprintf(str, "reach : %d", obj->GetParam()->attackReach_);
		debugText_->Render(str, 0, 70);
		sprintf(str, "def_ : %d", obj->GetParam()->def_);
		debugText_->Render(str, 0, 90);
		sprintf(str, "moveSpeed: %f", obj->GetParam()->moveSpeed_);
		debugText_->Render(str, 0, 110);
		sprintf(str, "targetAlive: %d", obj->GetTarget()->GetAliveFlg());
		debugText_->Render(str, 0, 130);
		sprintf(str, "targetType: %d", obj->GetTarget()->GetCharaType());
		debugText_->Render(str, 0, 150);
		sprintf(str, "count : %d", enemyList_.size());
		debugText_->Render(str, 0, 350);
		sprintf(str, "ins : %f", insTime_);
		debugText_->Render(str, 0, 370);
		sprintf(str, "push : %f", pushTime_);
		debugText_->Render(str, 0, 390);*/
	}
}