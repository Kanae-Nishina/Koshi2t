//	@file			CD3DXMesh_Anim.h
//	@brief		���b�V���̓ǂݍ���,�A�j���[�V����
//	@authoe	�搶

#include <stdio.h>
#include <windows.h>
#include<d3dx9.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

//�}�N��
#define SAFE_RELEASE(x) if(x){x->Release(); x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}
#define SAFE_DELETE_ARRAY(p){ if(p){ delete[] (p);   (p)=NULL;}}

//�\���̒�`
struct BufferPerMesh
{
	D3DXMATRIX mW;//���[���h�s��
	D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
	D3DXVECTOR4 vLightDir;//���C�g����
	D3DXVECTOR4 vEye;//�J�����ʒu
};

struct BufferPerMaterial
{
	D3DXVECTOR4 vAmbient;//�A���r�G���g��
	D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
	D3DXVECTOR4 vSpecular;//���ʔ���
};

//�I���W�i���@�}�e���A���\����
struct MyMaterial
{
	CHAR szName[100];
	D3DXVECTOR4 Ambient;//�A���r�G���g
	D3DXVECTOR4 Diffuse;//�f�B�t���[�Y
	D3DXVECTOR4 Specular;//�X�y�L�����[
	CHAR szTextureName[256];//�e�N�X�`���[�t�@�C����
	ID3D11ShaderResourceView* pTexture;
	DWORD dwNumFace;//���̃}�e���A���ł���|���S����
	MyMaterial()
	{
		ZeroMemory(this,sizeof(MyMaterial));
	}
	~MyMaterial()
	{
		SAFE_RELEASE(pTexture);
	}
};
//���_�̍\����
struct MyVertexTex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
	D3DXVECTOR2 vTex;
};

struct MyVertexNotex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
};

//�p�[�c���b�V���@�A�v����`���b�V��(�X�^�e�B�b�N���b�V���̃T���v���ɂ�����CD3DXMESH�N���X�Ɠ����j
struct PartsMesh
{
	DWORD dwNumMaterial;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer** ppIndexBuffer;
	char TextureFileName[8][256];//�e�N�X�`���[�t�@�C�����i�W���܂Łj
	MyMaterial* pMaterial;
	bool Tex;
};
//�h���t���[���\����
struct MyFrame: public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
	PartsMesh* pPartsMesh;
	MyFrame()
	{
		ZeroMemory(this,sizeof(MyFrame));
	}
};
//���b�V���R���e�i�[�\���� �t���[�����Ŏg�p
struct MYMESHCONTAINER: public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
};
//X�t�@�C�����̃A�j���[�V�����K�w��ǂ݉����N���X�B
class MyHierarchy: public ID3DXAllocateHierarchy
{
public:
	MyHierarchy(){}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR ,CONST D3DXMESHDATA* ,CONST D3DXMATERIAL* , 
		CONST D3DXEFFECTINSTANCE* , DWORD , CONST DWORD *, LPD3DXSKININFO , LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME );
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER );
};

//
//
//
class CD3DXMesh_Anim
{
public:
	//Data
	HWND m_hWnd;
	DWORD m_dwNumMaterial;
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_vPos;
	float m_fYaw,m_fPitch,m_fRoll;
	float m_fScale;
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;
	D3DXVECTOR3 m_LightDir;
	D3DXVECTOR3 m_Eye;
	D3DXVECTOR3 m_AxisX;
	D3DXVECTOR3 m_AxisY;
	D3DXVECTOR3 m_AxisZ;
	//�A�j���֘A
	MyHierarchy* m_pHierarchy;
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

	//Method
	CD3DXMesh_Anim();
	~CD3DXMesh_Anim();
	HRESULT Init(HWND hWnd,ID3D11Device*,ID3D11DeviceContext*,LPSTR);
	HRESULT InitDx9();
	HRESULT InitShader();
	void Render(D3DXMATRIX& mView,D3DXMATRIX& mProj,D3DXVECTOR3& vLight,D3DXVECTOR3& vEye);
	HRESULT LoadXAnimMesh(LPSTR FileName);
	void BuildAllMesh(D3DXFRAME* pFrame);
	HRESULT CreateAppMeshFromD3DXMesh(LPD3DXFRAME pFrame);
	void DrawFrame(LPD3DXFRAME p);
	void DrawPartsMesh(PartsMesh* p,D3DXMATRIX World);
	void UpdateHierarchyMatrices(D3DXFRAME* p,LPD3DXMATRIX pParentMatrix);
};