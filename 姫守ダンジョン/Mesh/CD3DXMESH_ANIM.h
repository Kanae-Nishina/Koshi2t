#pragma once
#include "./../Origin.h"

//�\���̒�`
struct BUFFER_PER_MESH
{
	D3DXMATRIX mW;//���[���h�s��
	D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
	D3DXVECTOR4 vLightDir;//���C�g����
	D3DXVECTOR4 vEye;//�J�����ʒu
};

struct BUFFER_PER_MATERIAL
{
	D3DXVECTOR4 vAmbient;//�A���r�G���g��
	D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
	D3DXVECTOR4 vSpecular;//���ʔ���
};

//�I���W�i���@�}�e���A���\����
struct MY_MATERIAL
{
	CHAR szName[100];
	D3DXVECTOR4 Ambient;//�A���r�G���g
	D3DXVECTOR4 Diffuse;//�f�B�t���[�Y
	D3DXVECTOR4 Specular;//�X�y�L�����[
	CHAR szTextureName[256];//�e�N�X�`���[�t�@�C����
	ID3D11ShaderResourceView* pTexture;
	DWORD dwNumFace;//���̃}�e���A���ł���|���S����
	MY_MATERIAL()
	{
		ZeroMemory(this, sizeof(MY_MATERIAL));
	}
	~MY_MATERIAL()
	{
		SAFE_RELEASE(pTexture);
	}
};
//���_�̍\����
struct MY_VERTEX_TEX
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
	D3DXVECTOR2 vTex;
};

struct MY_VERTEX_NOTEX
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
};

//�p�[�c���b�V���@�A�v����`���b�V��(�X�^�e�B�b�N���b�V���̃T���v���ɂ�����CD3DXMESH�N���X�Ɠ����j
struct PARTS_MESH
{
	DWORD dwNumMaterial;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer** ppIndexBuffer;
	char TextureFileName[8][256];//�e�N�X�`���[�t�@�C�����i�W���܂Łj
	MY_MATERIAL* pMaterial;
	bool Tex;
};
//�h���t���[���\����
struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
	PARTS_MESH* pPartsMesh;
	MYFRAME()
	{
		ZeroMemory(this, sizeof(MYFRAME));
	}
};
//���b�V���R���e�i�[�\���� �t���[�����Ŏg�p
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
};
//X�t�@�C�����̃A�j���[�V�����K�w��ǂ݉����N���X�B
class MY_HIERARCHY : public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY() {}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD *, LPD3DXSKININFO, LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
};

//
//
//
class CD3DXMESH_ANIM
{
public:
	//Data
	D3DXMATRIX m_World;
	HWND m_hWnd;
	DWORD m_dwNumMaterial;
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_Dir;
	float m_fYaw, m_fPitch, m_fRoll;
	float m_fScale;
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;
	D3DXVECTOR3 m_LightDir;
	D3DXVECTOR3 m_Eye;
	D3DXVECTOR3 m_AxisX;
	D3DXVECTOR3 m_AxisY;
	D3DXVECTOR3 m_AxisZ;
	//�A�j���֘A
	MY_HIERARCHY* m_pHierarchy;
	LPD3DXFRAME m_pFrameRoot;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	//Dx9
	LPDIRECT3D9 m_pD3d9;
	LPDIRECT3DDEVICE9 m_pDevice9;
	//Dx11
	ID3D11Device* m_pDevice11;
	ID3D11DeviceContext *m_pDeviceContext11;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11InputLayout* m_pVertexLayout_NoTex;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11VertexShader* m_pVertexShaderNoTex;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11PixelShader* m_pPixelShaderNoTex;
	ID3D11Buffer* m_pConstantBuffer0;
	ID3D11Buffer* m_pConstantBuffer1;
	ID3D11SamplerState* m_pSampleLinear;//�e�N�X�`���[�̃T���v���[

	LPD3DXANIMATIONSET m_pAnimSet[100];//100�܂ł̃A�j���[�V�����Z�b�g�ɑΉ�

									   //Method
	CD3DXMESH_ANIM();
	~CD3DXMESH_ANIM();
	HRESULT Init(HWND hWnd, ID3D11Device*, ID3D11DeviceContext*, LPSTR);
	HRESULT InitDx9();
	HRESULT InitShader();
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vEye);
	HRESULT LoadXAnimMesh(LPSTR FileName);
	void BuildAllMesh(D3DXFRAME* pFrame);
	HRESULT CreateAppMeshFromD3DXMesh(LPD3DXFRAME pFrame);
	void DrawFrame(LPD3DXFRAME p);
	void DrawPartsMesh(PARTS_MESH* p, D3DXMATRIX World);
	void UpdateHierarchyMatrices(D3DXFRAME* p, LPD3DXMATRIX pParentMatrix);

	void ChangeMotion(int index);	//�A�j���[�V�������[�V�����ύX
};