//
//	@file	Camera.h
//	@brief	�J�����֘A
//	@date	2016/11/08
//	@outher	�m�ȍ��c
//	@note	������(2016/11/08)
#pragma once
#include "./Origin.h"

class Camera
{

public:
	Camera();
	~Camera();
	void Render(D3DXMATRIX mView,D3DXMATRIX mProj);	//�`�揈��
};

