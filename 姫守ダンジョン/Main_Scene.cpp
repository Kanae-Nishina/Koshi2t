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
	virChar_[player1] = new SwordMan(player1);
	virChar_[player2] = new Witch(player2);
	virChar_[player3] = new ShieldMan(player3);
	virChar_[player4] = new Bomber(player4);

	for (int i = 0; i < 4; i++)
	{
		charList_.push_back(virChar_[i]);
	}

	ray_ = new Collision;
	virEnemy_ = new EnemyJobManager *[3];
	virEnemy_[0] = new Slim;

	charList_.push_back(virEnemy_[0]);
}

//
//	@brief	�f�X�g���N�^
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;

	delete ray_;
	ray_ = nullptr;

	delete virEnemy_[0];
	virEnemy_[0] = nullptr;

	for (int i = 0; i < 4; i++)
	{
		delete virChar_[i];
		virChar_[i] = nullptr;
	}
	delete[] virChar_;
	virChar_ = nullptr;

	delete debugText_;
	debugText_ = nullptr;
}

//
//	@brief						������
//	@param (m_hWnd)				�E�B���h�E�̃n���h��
//	@param (m_pDevice)			�f�o�C�X
//	@param (m_pDeviceContext)	�f�o�C�X�R���e�L�X�g
void Main_Scene::Init(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext)
{
	//�ǂݍ���X�t�@�C���̏���ǂݍ���
	XFileRead* xfileRead = new XFileRead;
	xfileRead->ReadXFilePath();

	//�X�e�[�W�̃t�@�C���ǂݍ���
	XFile* xfile = xfileRead->GetXFile("�X�e�[�W");
	stage_->Read(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());

	//���L�����t�@�C���ǂݍ���
	xfile = xfileRead->GetXFile("���m");
	virChar_[player1]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player1]->m_vPos = D3DXVECTOR3(26, 0, 11);

	xfile = xfileRead->GetXFile("�����m");
	virChar_[player2]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player2]->m_vPos = D3DXVECTOR3(26, 0, -11);

	xfile = xfileRead->GetXFile("���m");
	virChar_[player3]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player3]->m_vPos = D3DXVECTOR3(-26, 0, 11);

	xfile = xfileRead->GetXFile("���e�m");
	virChar_[player4]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
	virChar_[player4]->m_vPos = D3DXVECTOR3(-26, 0, -11);

	xfile = xfileRead->GetXFile("�X���C��");
	virEnemy_[0]->CharaInit(m_hWnd, m_pDevice, m_pDeviceContext, xfile->GetFileName());
}

//
//	@brief	�f�o�b�O�p������
HRESULT Main_Scene::DebugInit(ID3D11DeviceContext* m_pDeviceContext)
{
	debugText_ = new D3D11_TEXT;
	D3DXVECTOR4 vColor(1, 1, 1, 1);
	if (FAILED(debugText_->Init(m_pDeviceContext, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor)))
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

	for (int i = 0; i < 3; i++)
	{
		virEnemy_[0]->SetTargetChar(virChar_[i],virChar_[player4]);
	}
	//virEnemy_[0]->CharaUpdate();

	/*ray_->CharaNear(virChar_[player1]->m_vPos, virEnemy_[0]->m_vPos, 50.0);*/

	//���L�����X�V
	for (auto chara : charList_)
	{
		chara->CharaUpdate();
	}

	//�Փ˔���̍X�V
	CollisionControl();

	//�L�����̈ړ��X�V
	for (auto chara : charList_)
	{
		chara->Move_Update();
	}
}

//
//	@brief	�Փ˔���Ǘ�
void Main_Scene::CollisionControl()
{
	float fDistance = 0;
	D3DXVECTOR3 vNormal;
	//�ǂƂ̏Փ˔���

	//bool wallFlg = false;
	for (auto chara : charList_)
	{
		if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.3)
		{
			//�������ԂȂ̂ŁA���点��
			//virChar_[player1]->m_vPos = ray_->Slip(virChar_[player1]->m_Dir, vNormal);//����x�N�g�����v�Z
			chara->SlipMove(ray_->Slip(chara->m_Dir, vNormal));
			//����x�N�g����̕ǂƂ̃��C���� �Q�d�ɔ���	
			if (ray_->RayIntersect(chara, stage_->GetMeshInfo(), &fDistance, &vNormal) && fDistance <= 0.2)
			{
				//virChar_[player1]->m_vPos = D3DXVECTOR3(0, 0, 0);//�~�߂�
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
	//virChar_[player1]->SetHitWall(wallFlg);

	//�L�����N�^�[���m�̏Փ˔���
	}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Main_Scene::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	//�X�e�[�W�̕`��
	stage_->Render(mView, mProj);

	virEnemy_[0]->CharaRender(mView, mProj);

	//���L�����`��
	for (int i = 0; i < 4; i++)
	{
		virChar_[i]->CharaRender(mView, mProj);
	}

	//�f�o�b�O�`��
	char str[256];
	sprintf(str, "Atk(n-1 | s-2) : %d", virChar_[player1]->GetAtkState());
	debugText_->Render(str, 0, 10);
	sprintf(str, "AtkCount : %d", virChar_[player1]->GetAtkCnt());
	debugText_->Render(str, 0, 30);
	sprintf(str, "axis : %f", virChar_[player1]->m_AxisZ.z);
	debugText_->Render(str, 0, 50);
	sprintf(str, "count : %i", ray_->GetHitCnt());
	debugText_->Render(str, 0, 70);
	sprintf(str, "pos x : %f :pos z : %f", virEnemy_[0]->GetTargetPos().x, virEnemy_[0]->GetTargetPos().z );
	debugText_->Render(str, 0, 90);

}