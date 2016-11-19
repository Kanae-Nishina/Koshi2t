//
//	@file	CharactorManager.h
//	@brief	�L�����N�^�[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c

#pragma once
#include <vector>
#include "./../Origin.h"
#include "./../Mesh/CD3DXMESH_ANIM.h"
#include "./../Collision.h"

//#include "./../DebugDraw/D3D11_TEXT.h"

class CharactorManager:public CD3DXMESH_ANIM
{
protected:

	Collision* collision_;

	float opponentWeight_;	//�i�s�����ɂ���L�����̏d��
	
	bool aliveFlg_;		//�����t���O

	std::vector<CharactorManager*> aroundCharaList_;

	virtual void Move(float speed) = 0;					//�ړ�
	virtual void Attack() = 0;							//�U��
	virtual void Dead() = 0;							//���S
	virtual void Motion_Update()=0;						//���[�V�����X�V
	void KnockBack(D3DXVECTOR3 atkPos, float distance);	//�m�b�N�o�b�N
	void Rotation(D3DXVECTOR3 dirVec);					//�L�����̉�]
	void ArouncCharaCheck();							//���ӂɂ���L�������܂����ӂɂ��邩�̃`�F�b�N
public:
	CharactorManager();
	virtual ~CharactorManager();

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)=0;		//�������E�ǂݍ���
	virtual void CharaUpdate()=0;								//�X�V
	void CharaRender(D3DXMATRIX mView,D3DXMATRIX mProj);		//�`��
	//void CharaDestroy();										//���
	void SlipMove(D3DXVECTOR3 slopVec);							//�Ǌ���p�ړ�
	void StopMove();											//�Î~�p
	void Move_Update();											//�ړ��̍X�V

	void SetAroundChara(CharactorManager* charactor);	//���ӂɂ���L�����N�^�[�����X�g�ɃZ�b�g
	void SetOppWeight(float weight);					//�i�s�����ɂ���L�����N�^�[�̏d���Z�b�g

	bool GetAliveFlg() { return aliveFlg_; };

	int GetCount()const { return aroundCharaList_.size(); };	//�f�o�b�O�p�L�����J�E���g
};

