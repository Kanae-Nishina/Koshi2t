//
//	@file	CharactorManager.h
//	@brief	�L�����N�^�[�Ǘ��N���X
//	@date	2016/11/09
//	@author	�m�ȍ��c
//	@author	�g�z��R(�T�E���h)

#pragma once
#include <vector>
#include "./../Origin.h"
#include "./../Mesh/CD3DXSKINMESH.h"
#include "./../Collision.h"
#include "./../Read/MotionRead.h"
#include "./../Sound/Sound.h"
#include "./../Read/MotionRead.h"
#include "./../Read/ParameterRead.h"
#include "./../Read/XFileRead.h"
#include "./CharactorCreator.h"

//#include "./../DebugDraw/D3D11_TEXT.h"
enum CharaType
{
	Player1=0,
	Player2,
	Player3,
	Player4,
	PrincessT,
	Enemy,
	Non=100,
};


class CharactorManager//:public CD3DXSKINMESH
{
protected:
	CD3DXSKINMESH* mesh_;
	CharactorCreator* creator_;
	//bool effectFlg_;

	Motion* motion_;			//���[�V�����Ǘ��N���X
	unsigned int motionNo_;		//���݂̃��[�V�����ԍ�
	unsigned int motionCount_;	//���[�V�����p�J�E���g
	unsigned int motionFrame_;	//���݂̃��[�V�����̑��t���[����
	bool motionChange_;			//���[�V�����ύX�t���O
	float motionSpeed_;			//���[�V�����X�s�[�h
	float motionPlayPos_;		//���[�V�����̍Đ��ʒu

	float knockBackDis_;		//�m�b�N�o�b�N����
	float knockBackSpeed_;		//�m�b�N�o�b�N�X�s�[�h
	bool knockBackFlg_;			//�m�b�N�o�b�N�t���O
	D3DXVECTOR3 knockBackPos_;	//�m�b�N�o�b�N�J�n���W

	CharaType perpetrator_;		//�Ō�ɍU�����Ă����L�����N�^�[
	Collision* collision_;		//�Փ˔���N���X
	unsigned int hp_;			//���݂�HP
	bool aliveFlg_;				//�����t���O

	unsigned int damageCount_;		//�_���[�W���_�ŕ`��J�E���g�A�b�v
	unsigned int damageDrawTime_;	//�_���[�W���_�ŕ`�掞��
	bool damageFlg_;				//�_���[�W�t���O

	unsigned int spaceNo_;		//���W�ɂ���Ԕԍ�
	float opponentWeight_;		//�i�s�����ɂ���L�����̏d��
	bool moveAbleFlg_;			//�ړ��\�t���O
	bool wallHitFlg_;			//�ǂƂ̏Փ˃t���O
	D3DXVECTOR3 ownPush_;		//�����������Ă�������x�N�g��


	CharaType charaType_;								//�����̃L�����N�^�[�^�C�v
	std::vector<CharactorManager*> aroundCharaList_;	//���ӂɂ���L����

	virtual void Move(float speed) = 0;					//�ړ�
	virtual void Attack() = 0;							//�U��
	virtual void Dead() = 0;							//���S
	virtual void MoveCharaHit();						//�ړ������ɃL�����N�^�[�����邩�ǂ���
	void Rotation(D3DXVECTOR3 dirVec);					//�L�����̉�]
	void AroundCharaCheck();							//���ӂɃL�����N�^�[�����邩�ǂ���
	virtual void ChangeMotion(Motion* motion,char* name);		//���[�V�����̕ύX
	virtual void DamageSound() {};						//�_���[�W�T�E���h
	virtual void SetParameter(char* name)=0;
public:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Dir;
	float m_Yaw;
	D3DXVECTOR3 m_Scale;

	CharactorManager();
	virtual ~CharactorManager();
	
	static std::vector<CharactorManager*> allCharaList_;		//�S�ẴL����
	virtual void CharaInit(char* name);		//�������E�ǂݍ���
	virtual void CharaUpdate()=0;								//�X�V
	virtual void Reset()=0;										//���Z�b�g
	virtual void CharaRender();									//�`��
	virtual void Move_Update();									//�ړ��̍X�V
	virtual void DamageCalc(unsigned int atk)=0;				//�_���[�W�v�Z
	void Destroy();												//���
	void SetMotionData(Motion* motionData);
	void KnockBack(D3DXVECTOR3 atkPos, float distance,float speed);	//�m�b�N�o�b�N

	void SlipMove(D3DXVECTOR3 slopVec);							//�Ǌ���p�ړ�
	void StopMove();											//�Î~�p
	void SetAroundChara(CharactorManager* charactor);			//���ӂɂ���L�����N�^�[�����X�g�ɃZ�b�g
	//void SetAllCharaList(std::vector<CharactorManager*> list);	//���݂��Ă���S�ẴL�����N�^�[�Z�b�g
	void SetOppWeight(float weight);							//�i�s�����ɂ���L�����N�^�[�̏d���Z�b�g
	void SetKnockBack(D3DXVECTOR3 pos, float dist,float speed,CharaType charatype);	//�m�b�N�o�b�N���Z�b�g
	void SetKnockBackFlg(bool flg) { knockBackFlg_ = flg; };	//�m�b�N�o�b�N�t���O�Z�b�g
	void SetWallHitflg(bool flg) { wallHitFlg_ = flg; };		//�ǂƂ̏Փ˃t���O�Z�b�g
	int GetSpaceNo();											//��Ԕԍ��擾
	bool GetAliveFlg() { return aliveFlg_; };					//�����t���O�擾
	bool GetKnockBackFlg() { return knockBackFlg_; };			//�m�b�N�o�b�N�t���O�擾
	bool GetDamageFlg() { return damageFlg_; };					//�_���[�W�t���O�擾
	bool GetWallHitFlg() { return wallHitFlg_; };				//�ǂƂ̏Փ˃t���O�擾
	CharaType GetCharaType()const;								//�L�����N�^�[�^�C�v�擾

	//�f�o�b�O�p
	int GetAroundC() { return aroundCharaList_.size(); };		//���g�̎��ӂɂ���L�����N�^�[�̐��擾
	unsigned int GetHP()const { return hp_; };					//���g�̗͎̑擾
	unsigned int GetMotionNo()const { return motionNo_; };		//���g�̃��[�V�����ԍ��擾
	float GetMotionSpeed()const { return motionSpeed_; };		//���g�̃��[�V�����X�s�[�h�擾
	unsigned int GetMotionCount()const { return motionCount_; };//���[�V�����J�E���g�擾
};

