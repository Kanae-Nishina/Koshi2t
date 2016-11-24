#pragma once
#include <list>
#include "./CharactorManager.h"
#include "./Player/PlayerManager.h"


class Princess :public CharactorManager
{
private:
	std::list<PlayerManager*> deadCharaList_;	//���񂾃v���C���[���X�g
	D3DXVECTOR3 destination_;		//�ړ��ړI�n
	float moveSpeed_;				//�ړ����x
	unsigned int sealTime_;			//����ɂ����鎞��
	unsigned int revivalTime_;		//�h���ɂ����鎞��

	virtual void Move(float speed);	//�ړ�
	virtual void Motion_Update();	//���[�V�����X�V
	virtual void Dead() {};
	virtual void Attack() {};
	void Seal();			//����
	void Resuscitation();			//�h��
public:
	Princess();
	virtual ~Princess();

	virtual void CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName);		//�������E�ǂݍ���
	virtual void CharaUpdate();						//�X�V
	virtual void DamageCalc(unsigned int atk);		//�_���[�W�v�Z
	void SetDestination(D3DXVECTOR3 pos);			//�ړI�n�Z�b�g
	void SetDeadCharaList(PlayerManager* chara);
};

