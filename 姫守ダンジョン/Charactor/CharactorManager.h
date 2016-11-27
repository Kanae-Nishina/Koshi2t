//
//	@file	CharactorManager.h
//	@brief	�L�����N�^�[�Ǘ��N���X
//	@date	2016/11/09
//	@outher	�m�ȍ��c

#pragma once
#include <vector>
#include "./../Origin.h"
#include "./../Mesh/CD3DXSKINMESH.h"
#include "./../Collision.h"
#include "./../Read/MotionRead.h"

//#include "./../DebugDraw/D3D11_TEXT.h"
enum CharaType
{
	Player1=0,
	Player2,
	Player3,
	Player4,
	PrincessT,
	Enemy,
};


class CharactorManager:public CD3DXSKINMESH
{
protected:
	Motion* motion_;

	CharaType charaType_;
	Collision* collision_;
	unsigned int hp_;
	unsigned int motionNo_;
	unsigned int motionCount_;
	float motionSpeed_;
	float opponentWeight_;	//�i�s�����ɂ���L�����̏d��
	float ownWright_;		//���g�̏d��
	bool aliveFlg_;			//�����t���O
	bool moveAbleFlg_;		//�ړ��\�t���O
	D3DXVECTOR3 ownPush_;	//�����������Ă�������x�N�g��

	float knockBackDis_;
	float knockBackSpeed_;
	bool knockBackFlg_;
	D3DXVECTOR3 knockBackPos_;

	std::vector<CharactorManager*> aroundCharaList_;	//���ӂɂ���L����
	std::vector<CharactorManager*> allCharaList_;		//�S�ẴL����
	virtual void Move(float speed) = 0;					//�ړ�
	virtual void Attack() = 0;							//�U��
	virtual void Dead() = 0;							//���S
	void Rotation(D3DXVECTOR3 dirVec);					//�L�����̉�]
	void AroundCharaCheck();
	void MoveCharaHit();
public:
	CharactorManager();
	virtual ~CharactorManager();

	virtual const char* CharaInit(const char* fileName)=0;		//�������E�ǂݍ���
	virtual void CharaUpdate()=0;								//�X�V
	virtual void CharaRender();									//�`��
	virtual void Move_Update();									//�ړ��̍X�V
	virtual void DamageCalc(unsigned int atk) = 0;				//�_���[�W�v�Z
	void SetMotionData(Motion* motionData);
	void KnockBack(D3DXVECTOR3 atkPos, float distance,float speed);	//�m�b�N�o�b�N

	void SlipMove(D3DXVECTOR3 slopVec);							//�Ǌ���p�ړ�
	void StopMove();											//�Î~�p
	void SetAroundChara(CharactorManager* charactor);			//���ӂɂ���L�����N�^�[�����X�g�ɃZ�b�g
	void SetAllCharaList(std::vector<CharactorManager*> list);
	void SetOppWeight(float weight);							//�i�s�����ɂ���L�����N�^�[�̏d���Z�b�g
	void SetKnockBack(D3DXVECTOR3 pos, float dist,float speed);
	bool GetAliveFlg() { return aliveFlg_; };
	CharaType GetCharaType()const;

	unsigned int GetHP()const { return hp_; };
};

