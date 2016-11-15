//
//	@file	Main_Scene.h
//	@brief	���C���Q�[���V�[���Ǘ��N���X
//	@date	2016/11/08
//	@outher	�m�ȍ��c
#pragma once
#include <vector>
#include "./Origin.h"
#include "./Read/XFileRead.h"
#include "./Stage/Stage.h"
#include "./Charactor/Player/JobManager.h"
#include "./Charactor/CharactorCreator.h"
#include "./DebugDraw/D3D11_TEXT.h"

class Main_Scene
{
	Stage* stage_;				//�X�e�[�W���
	JobManager** virChar_;		//�m�F�p���L�����N�^�[

	void CollisionControl();	//�Փ˔���Ǘ�

	//�f�o�b�N
	D3D11_TEXT* debugText_;
public:
	Main_Scene();
	~Main_Scene();

	void Init(HWND m_hWnd,ID3D11Device* m_pDevice,ID3D11DeviceContext* m_pDeviceContext);	//������
	
	HRESULT DebugInit(ID3D11DeviceContext* m_pDeviceContext);								//�f�o�b�O�`�揉����
	
	void Update();																			//�X�V
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj);										//�`��
};

