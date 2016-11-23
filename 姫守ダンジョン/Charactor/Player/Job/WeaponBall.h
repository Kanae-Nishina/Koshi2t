#pragma once
#include "./../../../Origin.h"
#include "./../../CharactorManager.h"

//
//	@brief	��ѓ���(�����m�Ɣ��e�m)
class WeaponBall
{
private:
	Collision* col_;
	STATICMESH::CD3DXMESH* weaponBall_;
	std::vector<CharactorManager*> damageList_;	//��e����\���̂���L�����N�^�[���X�g
	bool delFlg_;
	int delCount_;
	unsigned int atk_;
	float range_;
	float dist_;
	D3DXVECTOR3 startPos_;
	D3DXVECTOR3 dir_;
	void Hit();
public:
	WeaponBall(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, D3DXVECTOR3 pos);
	~WeaponBall();
	void SetDir(D3DXVECTOR3 dir);
	void SetScale(float scale);
	void Move_Weapon(float dist);
	void Time_Del_Weapon(int frame);
	void SetDamageList(std::vector<CharactorManager*> chara,CharaType cType);
	void SetDamageChara(CharactorManager* chara);
	void SetAttack(unsigned int atk);
	void SetHitRangeKnockBackDist(float range, float dist);
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj);
	bool GetDelFlg()const;
	float GetHitRange()const;
	float GetKnockBackDist()const;
	D3DXVECTOR3 GetPosition()const;
};