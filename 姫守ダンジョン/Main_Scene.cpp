//
//	@file	Main_Scene.cpp
//	@brief	�Q�[�����C���V�[���Ǘ�
//	@date	2016/11/08
//	@outher	�m�ȍ��c

#include "Main_Scene.h"

//
//	@brief	�R���X�g���N�^
Main_Scene::Main_Scene()
{
	stage_ = new Stage;
	virChar_ = new JobManager *[4];
	virChar_[Player1] = new SwordMan(CharaType::Player1);
	virChar_[Player2] = new Witch(CharaType::Player2);
	virChar_[Player3] = new ShieldMan(CharaType::Player3);
	virChar_[Player4] = new Bomber(CharaType::Player4);

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(virChar_[i]);
	}
	//virEnemy_ = new Slim;

}

//
//	@brief	�f�X�g���N�^
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	//delete ray_;
	//ray_ = nullptr;

	for (int i = 0; i < 4; i++)
	{
		delete virChar_[i];
		virChar_[i] = nullptr;
	}
	delete[] virChar_;
	virChar_ = nullptr;

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
	//delete[] virEnemy_;
	//virEnemy_ = nullptr;


	delete debugText_;
	debugText_ = nullptr;

	delete xfile;
	xfile = nullptr;
	delete parameter;
	parameter = nullptr;
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

	//�ǂݍ���X�t�@�C���̏���ǂݍ���
	xfileRead = new XFileRead;
	xfileRead->ReadXFilePath();

	//�ǂݍ��݃p�����[�^�f�[�^�̏���ǂݍ���
	parameter = new ParameterRead;
	parameter->SetJobParameter("./ReadData/JobParameterData.csv");
	//JobParameter* job = parameter->GetJobParamList("���m");

	//�X�e�[�W�̃t�@�C���ǂݍ���
	xfile = xfileRead->GetXFile("�X�e�[�W0");
	stage_->Read(wnd_, device_, deviceContext_, xfile->GetFileName(), xfile->GetFileName());

	//���L�����t�@�C���ǂݍ���
	xfile = xfileRead->GetXFile("���m");
	virChar_[Player1]->CharaInit(wnd_, device_, deviceContext_, xfile->GetFileName());
	virChar_[Player1]->SetParameter(parameter->GetJobParamList("���m"));
	virChar_[Player1]->m_Pos = D3DXVECTOR3(10, 0, -10);

	xfile = xfileRead->GetXFile("�����m");
	virChar_[Player2]->CharaInit(wnd_, device_, deviceContext_, xfile->GetFileName());
	virChar_[Player2]->SetParameter(parameter->GetJobParamList("�����m"));
	virChar_[Player2]->m_Pos = D3DXVECTOR3(5, 0, -10);

	xfile = xfileRead->GetXFile("���m");
	virChar_[Player3]->CharaInit(wnd_, device_, deviceContext_, xfile->GetFileName());
	virChar_[Player3]->SetParameter(parameter->GetJobParamList("���m"));
	virChar_[Player3]->m_Pos = D3DXVECTOR3(-5, 0, -10);

	xfile = xfileRead->GetXFile("���e�m");
	virChar_[Player4]->CharaInit(wnd_, device_, deviceContext_, xfile->GetFileName());
	virChar_[Player4]->SetParameter(parameter->GetJobParamList("���e�m"));
	virChar_[Player4]->m_Pos = D3DXVECTOR3(-10, 0, -10);

	//�G�l�~�[�̓ǂݍ���
	parameter->SetEnemyParameter("./ReadData/EnemyParameterData.csv");
	

	time_ = 0;


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
	D3DXVECTOR4 vColor(1, 1, 1, 1);
	if (FAILED(debugText_->Init(deviceContext_, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//
//	@brief	�X�V
void Main_Scene::Update()
{
	//�G�l�~�[�X�|�[������
	//if ((GetKeyState(VK_F1) & 0x80))
	//{
	//if (enemyCount < 1)
	if (++time_ % (FPS * 3) == 0)
	{
		auto virEnemy_ = new Slim;
		xfile = xfileRead->GetXFile("�X���C��");
		clock_t start = clock();
		virEnemy_->CharaInit(wnd_, device_, deviceContext_, xfile->GetFileName());
		clock_t end1 = clock();
		virEnemy_->SetParameter(parameter->GetEnemyParamList("�X���C��"));
		virEnemy_->SetTarget(virChar_[Player4]);
		clock_t end2 = clock();
		charList_.push_back(virEnemy_);
		enemyList_.push_back(virEnemy_);
		insTime_ = (double)(end1 - start) / CLOCKS_PER_SEC;
		pushTime_= (double)(end2 - start) / CLOCKS_PER_SEC;
	}

	//�G�l�~�[�^�[�Q�b�g�X�V
	if (!enemyList_.empty())
	{
		for (auto enemy : enemyList_)
		{
			//�v���C���[���[�v
			for (int i = 0; i < 3; i++)
			{
				//�v���C���[�ƃG�l�~�[�����̋�����
				float dist = 5.0;
				if (ray_->CharaNear(enemy->m_Pos, virChar_[i]->m_Pos, dist))
				{
					enemy->Target_Update(virChar_[i], virChar_[Player4]);
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

	//�Փ˔���̍X�V
	CollisionControl();

	//�L�����̈ړ��X�V
	for (auto chara : charList_)
	{
		chara->Move_Update();
	}

	//�G�l�~�[���S�����X�V
	EnemyDestroy();
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
		if (ray_->RayIntersect(chara, stage_->GetMeshWallInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
		{
			//�������ԂȂ̂ŁA���点��
			//virChar_[player1]->m_Pos = ray_->Slip(virChar_[player1]->m_Dir, vNormal);//����x�N�g�����v�Z
			chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
			//����x�N�g����̕ǂƂ̃��C���� �Q�d�ɔ���	
			if (ray_->RayIntersect(chara, stage_->GetMeshWallInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
			{
				//virChar_[player1]->m_Pos = D3DXVECTOR3(0, 0, 0);//�~�߂�
				chara->StopMove();
				//wallFlg = true;
			}
		}
		//���ӂɃL�����N�^�[�����邩�ǂ����̊m�F
		for (auto opp : charList_)
		{
			if (chara != opp)
			{
				//chara��opp�̋����𔻒�

				//�߂�������
				chara->SetAroundChara(opp);
				opp->SetAroundChara(chara);
			}
		}
	}

}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Main_Scene::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	//�X�e�[�W�̕`��
	stage_->Render(mView, mProj);

	//virEnemy_->CharaRender(mView, mProj);

	//���L�����`��
	/*for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaRender(mView, mProj);
	}*/
	for (auto chara : charList_)
	{
		chara->CharaRender(mView, mProj);
	}

	//�f�o�b�O�`��
	char str[256];
	sprintf(str, "Atk(no0,w1,na2,c3,sa4) : %d", virChar_[Player1]->GetAtkState());
	debugText_->Render(str, 0, 10);
	sprintf(str, "hp_ : %d", virChar_[Player1]->GetParam()->hp_);
	debugText_->Render(str, 0, 30);
	sprintf(str, "normalAtk_ : %d", virChar_[Player1]->GetParam()->normalAtk_);
	debugText_->Render(str, 0, 50);
	sprintf(str, "specialAtk_ : %d", virChar_[Player1]->GetParam()->specialAtk_);
	debugText_->Render(str, 0, 70);
	sprintf(str, "def_ : %d", virChar_[Player1]->GetParam()->def_);
	debugText_->Render(str, 0, 90);
	sprintf(str, "specialAttackTime_ : %f", virChar_[Player1]->GetParam()->specialAttackTime_);
	debugText_->Render(str, 0, 110);
	sprintf(str, "chargeTime_ : %d", virChar_[Player1]->GetParam()->chargeTime_);
	debugText_->Render(str, 0, 130);
	sprintf(str, "moveSpeed_ : %f", virChar_[Player1]->GetParam()->moveSpeed_);
	debugText_->Render(str, 0, 150);
	sprintf(str, "specialMoveSpeed_ : %f", virChar_[Player1]->GetParam()->specialMoveSpeed_);
	debugText_->Render(str, 0, 170);
	sprintf(str, "weight_ : %f", virChar_[Player1]->GetParam()->weight_);
	debugText_->Render(str, 0, 190);
	sprintf(str, "attackReach_ : %f", virChar_[Player1]->GetParam()->attackReach_);
	debugText_->Render(str, 0, 210);
	sprintf(str, "attackRange_ : %f", virChar_[Player1]->GetParam()->attackRange_);
	debugText_->Render(str, 0, 230);
	sprintf(str, "scale_ : %f", virChar_[Player1]->GetParam()->scale_);
	debugText_->Render(str, 0, 250);
	sprintf(str, "x : %f y :%f", virChar_[Player1]->m_Pos.x, virChar_[Player1]->m_Pos.z);
	debugText_->Render(str, 0, 270);
	if (!enemyList_.empty())
	{
		sprintf(str, "count : %d", enemyList_.size());
		debugText_->Render(str, 0, 350);
		sprintf(str, "ins : %f", insTime_);
		debugText_->Render(str, 0, 370);
		sprintf(str, "push : %f", pushTime_);
		debugText_->Render(str, 0, 390);
	}
	//float dist = pow(enemyList_[0]->m_Pos.x - virChar_[player1]->m_Pos.x, 2) + pow(virEnemy_->m_Pos.z - virChar_[player1]->m_Pos.z, 2);
	//sprintf(str, "dist: %f", dist);
	//debugText_->Render(str, 0, 90);
	/*sprintf(str, "count : %i", ray_->GetHitCnt());
	debugText_->Render(str, 0, 70);*/
	//sprintf(str, "pos x : %f :pos z : %f", virEnemy_->GetTargetPos().x, virEnemy_->GetTargetPos().z);
	//debugText_->Render(str, 0, 70);
	//sprintf(str, "pos x : %f :pos z : %f", virEnemy_->m_Pos.x, virEnemy_->m_Pos.z);
	//debugText_->Render(str, 0, 90);

}