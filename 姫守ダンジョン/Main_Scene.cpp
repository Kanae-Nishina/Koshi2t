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
}

//
//	@brief	�f�X�g���N�^
Main_Scene::~Main_Scene()
{
	delete stage_;
	stage_ = nullptr;
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
}

//
//	@brief	�X�V
void Main_Scene::Update()
{

}

//
//	@brief			�`��
//	@param (mView)	�`��p�}�g���b�N�X
//	@param (mProj)	�ˉe�ϊ��p�}�g���b�N�X
void Main_Scene::Render(D3DXMATRIX mView, D3DXMATRIX mProj)
{
	//�X�e�[�W�̕`��
	stage_->Render(mView, mProj);
}