//
//	@file	EnemyManager.h
//	@brief	�G�Ǘ��N���X
//	@date	2016/11/13
//	@outher	�g�z��R

#pragma once
#include "./../CharactorManager.h"
#include "./../../DebugDraw/D3D11_TEXT.h"



class EnemyManager : public CharactorManager
{
private:
	D3DXVECTOR3 targetPos_;
	enum TargetObject
	{
		princess = 0,
		player,
	};
	TargetObject targetObj_;
	
protected:

	CharactorManager* targetChar_;
	D3DXVECTOR3 getpos_;
	virtual void NormalAttack() = 0;	//�ʏ�U��
	virtual void Attack();				//�U��
	virtual void Move(float speed);		//�ړ�����
	virtual void Dead();				//���S
	virtual void Motion_Update() {};	//���[�V�����X�V

public:
	EnemyManager() ;
	virtual ~EnemyManager();
	
	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);		//�������E�ǂݍ���

	//void SetTargetChar(CharactorManager* checkChar, CharactorManager* princess);	//�߂��ɂ��邩����
	D3DXVECTOR3 GetTargetPos() { return targetPos_; };	//�^�[�Q�b�g�|�W�V�����擾�f�o�b�N�p
};

