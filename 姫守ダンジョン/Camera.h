//
//	@file	Camera.h
//	@brief	�J�����֘A
//	@date	2016/11/08
//	@author	�m�ȍ��c
#pragma once
#include <math.h>
#include "./Origin.h"

class Camera
{
	D3D11_TEXT* debugText_;


	D3DXMATRIX oriMat_, tran_, yaw_, pitch_;
	float temp_;
	D3DXVECTOR3 farPlayerPos_;

	float zoom;
	float zoomPow_;
	void DebugMove();		//�f�o�b�O�p�J�����ړ�
public:
	Camera();
	~Camera();

	static D3DXMATRIX mView_;
	static D3DXMATRIX mProj_;
	D3DXVECTOR3 movePow_;				//�ړ���
	D3DXVECTOR3 gazePoint_;				//�����_
	float dist_[4];

	void TitleUpdate(float radius);
	bool Main_Start_FirstUpdate();
	bool Main_Start_SecondUpdate();
	void Main_Game_Update();
	void Render();	//�`�揈��
	void SetPlayerPos(D3DXVECTOR3 pos,int no);
	D3DXVECTOR3 GetPos() { return movePow_; };
	float GetDist()const { return dist_[0]; };
	float GetZoom()const { return zoom; };
};

