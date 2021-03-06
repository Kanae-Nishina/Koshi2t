//
//	@file	EnemyManager.h
//	@brief	敵管理クラス
//	@date	2016/11/13
//	@author	吉越大騎
//	@author	仁科香苗

#pragma once
#include "./../CharactorManager.h"
#include "./../../DebugDraw/D3D11_TEXT.h"
#include "./../../Read/ParameterRead.h"
#include "./../Player/JobManager.h"

//	パラメータ
struct EnemyParam
{
	char name_[30];				//敵の名
	unsigned int hp_;			//HP
	unsigned int atk_;			//通常攻撃力
	unsigned int def_;			//守備力
	unsigned int waitTime_;		//待機時間
	float moveSpeed_;			//移動速度
	float attackReach_;			//攻撃距離
	float weight_;				//重さ
	float scale_;				//サイズ
};

class EnemyManager : public CharactorManager
{
private:
	enum TargetObject
	{
		princess = 0,
		player,
	};
	TargetObject targetObj_;
	D3DXVECTOR3 targetPos_;


	static std::vector<D3DXVECTOR3> busStop_;
	static std::vector<int> busStopSpaceNo_;


	void SetTargetPos(D3DXVECTOR3 pos);
protected:
	unsigned int atkWaitTime_;	//攻撃する間隔
	//char motionName_[10];		//現在再生しているモーション名
	float motionPlayPos_;		//モーションの再生位置

	EnemyParam* param_;
	CharactorManager* targetChar_;
	D3DXVECTOR3 getpos_;

	void Target_Update();
	virtual void ChangeMotion(Motion* motion, char* name);
	virtual void Move(float speed);		//移動処理
	virtual void Attack();
	virtual void NormalAttack() = 0;
	virtual void Dead();				//死亡
	virtual void DamageCalc(unsigned int atk);
	virtual void DamageSound() {};		//ダメージサウンド
	virtual void SetParameter(char* name);
public:
	EnemyManager();
	virtual ~EnemyManager();
	
	static CharactorManager* princess_;
	static std::vector<JobManager*> playerList_;

	virtual void CharaInit(char* name);		//初期化・読み込み
	virtual void CharaRender();				//描画

	static void SetBusStop(std::vector<D3DXVECTOR3> pos);
	void SetTarget(CharactorManager* chara);

	//void SetTargetChar(CharactorManager* checkChar, CharactorManager* princess);	//近くにいるか判別
	void SetModel(CD3DXSKINMESH* mesh);
	D3DXVECTOR3 GetTargetPos() { return targetPos_; };	//ターゲットポジション取得デバック用
	EnemyParam* GetParam() { return param_; };
	CharactorManager* GetTarget() { return targetChar_; };
};

