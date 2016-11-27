#pragma once
#include "./../../../Origin.h"
#include "./../../CharactorManager.h"

//
//	@brief	��ѓ���(�����m�Ɣ��e�m)
class WeaponBall
{
private:
	Collision* col_;
	CD3DXMESH* weaponBall_;
	std::vector<CharactorManager*> damageList_;	//��e����\���̂���L�����N�^�[���X�g
	bool delFlg_;
	int delCount_;
	unsigned int atk_;
	float dist_;
	float kDist_;
	float kSpeed_;
	D3DXVECTOR3 startPos_;
	D3DXVECTOR3 dir_;
	void Hit();
public:
	WeaponBall(D3DXVECTOR3 pos);
	~WeaponBall();
	void SetDir(D3DXVECTOR3 dir);
	void SetScale(float scale);
	void Move_Weapon(float dist,float speed);
	void Time_Del_Weapon(int frame);
	void SetDamageList(std::vector<CharactorManager*> chara,CharaType cType);
	void SetDamageChara(CharactorManager* chara);
	void SetAttack(unsigned int atk);
	void SetKnockBack(float dist, float kDist,float kSpeed);
	void Render();
	bool GetDelFlg()const;
	//float GetHitDist()const;
	//float GetKnockBackDist()const;
	D3DXVECTOR3 GetPosition()const;
};