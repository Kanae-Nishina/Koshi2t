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
	D3D11_TEXT* debugText_;						//�f�o�b�O�e�L�X�g
	D3DXMATRIX oriMat_, tran_, yaw_, pitch_;	//�}�g���b�N�X

	const float titleCmeraSpeed_;	//�^�C�g���V�[����]���x
	const float mainCameraSpeedF_;	//���C���V�[���ړ����x�A�J�n����
	const float mainCameraSpeedS_;	//���C���V�[���ړ����x�A�J�n��
	D3DXVECTOR3 firstMovePos_;		//���C���V�[���A�Q�[���J�n���̍��W
	D3DXVECTOR3 firstGazePos_;		//���C���V�[���A�Q�[���J�n���̒����_
	float mainDist_;				//�J�����ƒ����_�Ƃ�Z���W�̍���
	float zoom_;					//�Y�[���l
	void DebugMove();				//�f�o�b�O�p�J�����ړ�
public:
	Camera();
	~Camera();

	static D3DXMATRIX mView_;	//�r���[t�����X�t�H�[��		
	static D3DXMATRIX mProj_;	//�v���W�F�N�V�����g�����X�t�H�[��
	D3DXVECTOR3 movePow_;		//�ړ���
	D3DXVECTOR3 gazePoint_;		//�����_

	void TitleUpdate(float radius);			//�^�C�g����ʍX�V
	bool Main_Start_FirstUpdate();			//�Q�[�����C���J�n����X�V
	bool Main_Start_SecondUpdate();			//�Q�[�����C���J�n�X�V
	void Main_Game_Update();				//�Q�[�����C�����X�V
	void Render();							//�`�揈��
	float GetZoom()const { return zoom_; };	//�Y�[���l�擾
};

