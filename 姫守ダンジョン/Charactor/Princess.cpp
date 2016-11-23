#include "./Princess.h"

//
//	@brief	�R���X�g���N�^
Princess::Princess()
{
}

//
//	@brief	�f�X�g���N�^
Princess::~Princess()
{
}

//
//	@brief	������
void Princess::CharaInit(HWND m_hWnd, ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext, const char* fileName)
{
	char FileName[80] = { 0 };
	memset(FileName, 0, sizeof(FileName));
	strcpy_s(FileName, sizeof(FileName), "./Model/XFiles/Princess/");
	strcat_s(FileName, sizeof(FileName), fileName);
	CD3DXSKINMESH_INIT si;
	si.hWnd = m_hWnd;
	si.pDevice = m_pDevice;
	si.pDeviceContext = m_pDeviceContext;
	Init(&si);
	CreateFromX(FileName);
	m_Scale = D3DXVECTOR3(0.2, 0.2, 0.2);
}

//
//	@brief	�ړ�
void Princess::Move(float speed)
{
	//�����x�N�g��
	D3DXVECTOR3 move = { 0,0,0 };
	move.x = destination_.x - m_Pos.x;
	move.z = destination_.z - m_Pos.z;
	D3DXVec3Normalize(&move, &move);

	//��]
	Rotation(move);

	//�����Ă����������p�x���擾
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(m_Yaw)*-1, 0, cosf(m_Yaw)*-1);

	float sp = speed;
	m_Dir = D3DXVECTOR3(vec.x*sp*opponentWeight_, 0, vec.z*sp*opponentWeight_);

}

//
//	@brief	���[�V�����X�V
void Princess::Motion_Update()
{

}

//
//	@brief	�_���[�W�v�Z
//	@note	�P�̏ꍇ�͎��S
void Princess::DamageCalc(unsigned int atk)
{
	aliveFlg_ = false;
}

//
//	@brief	�ړI�n�Z�b�g
void Princess::SetDestination(D3DXVECTOR3 pos)
{
	destination_ = pos;
}

//
//	@brief	����
void Princess::Seal()
{

}

//
//	@brief	�h��
void Princess::Resuscitation()
{
	float resDist = 3;
	std::list<CharactorManager*> resList;
	if (!deadCharaList_.empty())
	{
		for (auto c : deadCharaList_)
		{
			if (collision_->CharaNear(m_Pos, c->m_Pos, resDist))
			{
				c->SetRevivalFlg();
				resList.push_back(c);
			}
		}
	}

	if (!resList.empty())
	{
		for (auto c : resList)
		{
			auto res = std::find(deadCharaList_.begin(), deadCharaList_.end(), c);
			deadCharaList_.erase(res);
		}
		resList.clear();
	}
}

//
//	@breif	���S�L�����Z�b�g
void Princess::SetDeadCharaList(PlayerManager* chara)
{
	deadCharaList_.push_back(chara);
}

//
//	@brief	�X�V
void Princess::CharaUpdate()
{
	//�ړ�
	float speed = 0.01;
	MoveCharaHit();
	Move(speed);

	//�h��
	Resuscitation();
}