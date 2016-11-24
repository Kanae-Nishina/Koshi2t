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
	D3DXVECTOR3 movePow_;				//�ړ���
	D3DXVECTOR3 gazePoint_;				//�����_
	D3DXMATRIX oriMat_, tran_, yaw_,pitch_;
	float dist_,temp_;
	D3DXVECTOR3 farPlayerPos_;

	float zoom;
	float zoomPow_;
	void DebugMove();		//�f�o�b�O�p�J�����ړ�
public:
	Camera();
	~Camera();
	
	D3DXMATRIX GetView()const { return mView_; };
	D3DXMATRIX GetProj()const { return mProj_; };
	void Update();	//�X�V
	void Render();	//�`�揈��
	void SetPlayerPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos() { return movePow_; };
	float GetDist()const { return dist_; };
	float GetZoom()const { return zoom; };
};

