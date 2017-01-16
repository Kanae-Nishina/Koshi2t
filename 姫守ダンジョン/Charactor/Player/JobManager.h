//
//	@file	JobManager.h
//	@brief	�E�Ɩ��̏���
//	@date	2016/11/10
//	@author	�m�ȍ��c

#pragma once
#include "./../Player/PlayerManager.h"
#include "./../../Read/ParameterRead.h"
#include "./../../Collision.h"
#include "./../../Mesh/CD3DXMESH.h"
#include "./Job/WeaponBall.h"
#include "./../../UI/TD_Graphics.h"

#define UI_SPACE	20		//�v���C���[1�Ɖ�ʒ[�̌���
#define UI_INTERVAL	480		//UI��UI�̊Ԋu(CharaType�ɏ�Z����)

//	�E�ƊǗ��N���X
class JobManager :public PlayerManager
{
protected:
	TD_Graphics* backUI_;
	TD_Graphics* jobMarkUI_;
	TD_Graphics* hpGageUI_;
	D3DXVECTOR2 backUIPos_;
	D3DXVECTOR2 jobUIPos_;
	D3DXVECTOR2 hpGazePos_;
	//unsigned int timeCount_;	//�U������
	//unsigned int timeAtkEnd_;		//�U���I������
	int attackCount_;			//�U���{�^���J�E���g
	Collision* col_;

	void UIRender();
	virtual void WeaponUpdate() {};
public:
	JobManager(CharaType charaType);
	virtual ~JobManager();

	virtual void CharaUpdate();
	//template<class> p;
	//void SetParameter(JobParameter* param);
	//PlayerParameter GetParam()const;

	int GetAtkCnt() { return attackCount_; };

	//�f�o�b�N�p
	PlayerParameter* GetParam()const { return param_; };
};

