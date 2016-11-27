#pragma once
#include "./../Origin.h"

//namespace STATICMESH
//{
	//�\���̒�`
struct SIMPLECONSTANT_BUFFER0
{
	D3DXMATRIX mW;//���[���h�s��
	D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
	D3DXVECTOR4 vLightDir;//���C�g����
	D3DXVECTOR4 vEye;//�J�����ʒu
};

struct SIMPLECONSTANT_BUFFER1
{
	D3DXVECTOR4 vAmbient;//�A���r�G���g��
	D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
	D3DXVECTOR4 vSpecular;//���ʔ���
};

//�I���W�i���@�}�e���A���\����
struct MY_MATERIAL
{
	CHAR szName[110];
	D3DXVECTOR4 Ambient;//�A���r�G���g
	D3DXVECTOR4 Diffuse;//�f�B�t���[�Y
	D3DXVECTOR4 Specular;//�X�y�L�����[
	CHAR szTextureName[110];//�e�N�X�`���[�t�@�C����
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
struct MY_VERTEX
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNorm;
	D3DXVECTOR2 vTex;
};

//
//
//�����܂ł����b�V���f�[�^���h�t�@�C��������o���������h���ړI�B�����_�[��Dx11�̂ق��ōs���B
class CD3DXMESH
{
private:
	DWORD m_dwNumMaterial;

	static D3DMATRIX m_View;
	static D3DMATRIX m_Proj;
	static D3DXVECTOR3 m_Light; 
	static D3DXVECTOR3 m_Eye;

	static HWND m_hWnd;
	//Dx9
	static LPDIRECT3D9 m_pD3d9;
	static LPDIRECT3DDEVICE9 m_pDevice9;
	D3DMATERIAL9* pMeshMaterials;
	DWORD m_NumAttr;
	DWORD m_AttrID[300];//300�����܂�
	bool m_Tex;

	//Dx11
	static ID3D11Device* m_pDevice11;
	static ID3D11DeviceContext *m_pDeviceContext11;
	static ID3D11InputLayout* m_pVertexLayout;
	static ID3D11InputLayout* m_pVertexLayoutNotex;
	static ID3D11VertexShader* m_pVertexShader;
	static ID3D11VertexShader* m_pVertexShaderNoTex;
	static ID3D11PixelShader* m_pPixelShader;
	static ID3D11PixelShader* m_pPixelShaderNoTex;
	static ID3D11Buffer* m_pConstantBuffer0;
	static ID3D11Buffer* m_pConstantBuffer1;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer** m_ppIndexBuffer;

	//resource
	char m_TextureFileName[8][256];//�e�N�X�`���[�t�@�C�����i�W���܂Łj
	ID3D11SamplerState* m_pSampleLinear;//�e�N�X�`���[�̃T���v���[
	MY_MATERIAL* m_pMaterial;
	//bool m_Texture;
public:

	//Data
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_vPos;
	float m_fYaw, m_fPitch, m_fRoll;
	float m_fScale;
	D3DXMATRIX m_World;

	//Method
	CD3DXMESH();
	~CD3DXMESH();
	//static HRESULT Init(HWND hWnd, ID3D11Device*, ID3D11DeviceContext*/*, LPSTR*/);
	//static HRESULT InitDx9();
	static HRESULT InitShader(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	HRESULT LoadXMesh(LPSTR FileName);
	//static HRESULT InitShader();
	//void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vEye);
	void Render(D3DXVECTOR3 pos, float rotY, float scale);
	static void SetCamera(D3DXMATRIX view, D3DXMATRIX proj);
};
//}