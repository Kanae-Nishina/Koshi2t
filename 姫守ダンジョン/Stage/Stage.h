//
//	@file	Stage.h
//	@brief	�X�e�[�W�֘A
//	@date	2016/11/07
//	@author	�m�ȍ��c

#pragma once
#include <vector>
#include "./../Mesh/CD3DXMESH.h"
#include "./../Camera.h"
#include "./../Read/XFileRead.h"
#include "./../Charactor/CharactorCreator.h"

class Stage
{
	CharactorCreator* creator_;		//���f���ǂݍ���
	static CD3DXMESH* stage_;		//�X�e�[�W���b�V��
public:
	Stage();
	~Stage();

	void Init(char* stageName);		//������
	void Render();					//�`��
	static CD3DXMESH* GetMeshInfo();//���b�V���̎擾
};