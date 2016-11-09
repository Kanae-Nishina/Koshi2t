//
//	@file	Camera.h
//	@brief	�J�����֘A
//	@date	2016/11/08
//	@outher	�m�ȍ��c
#pragma once
#include "./Origin.h"

class Camera
{
	D3D11_TEXT* debugText_;

	D3DXMATRIX mView_;
	D3DXMATRIX mProj_;
	D3DXVECTOR3 movePow_;	//�ړ���
	D3DXVECTOR3 gazePoint_;	//�����_
public:
	Camera();
	~Camera();
	
	D3DXMATRIX GetView()const { return mView_; };
	D3DXMATRIX GetProj()const { return mProj_; };
	void Update();	//�X�V
	void Render();	//�`�揈��
};

