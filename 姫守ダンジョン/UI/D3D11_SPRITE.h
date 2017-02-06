#pragma once
#include "./../Origin.h"
#define DIMENSION 12.0f
#define WDIMENSION 10.0f
#define TEX_DIMENSION 128.0f

//
//
struct SPRITE_CONSTANT_BUFFER
{
	D3DXMATRIX mWVP;
	D3DXVECTOR4 vColor;
	D3DXVECTOR4 fAlpha;
	D3DXVECTOR4 TexScroll;
};

//
class D3D11_SPRITE
{
private:
	static ID3D11Device* m_pDevice;
	static ID3D11DeviceContext* m_pDeviceContext;
	static ID3D11VertexShader* m_pVertexShader;
	static ID3D11PixelShader* m_pPixelShader;
	static ID3D11InputLayout* m_pVertexLayout;
	static ID3D11Buffer* m_pConstantBuffer;
	static ID3D11BlendState* m_pBlendState;
	static DWORD m_dwWindowWidth;
	static DWORD m_dwWindowHeight;
	static float m_fAlpha;
	static D3DXVECTOR4 m_vColor;
	static D3DXMATRIX m_View;
	static D3DXMATRIX m_Proj;

	ID3D11SamplerState* m_pSampleLinear;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pAsciiTexture;
	float m_fScale;
	float m_fYaw, m_fPitch, m_fRoll;
	D3DXVECTOR2 m_vSize;	//�A�j���[�V�����e�N�X�`���̉��A�c�T�C�Y
	int m_iAnimSpeed;		//�A�j���[�V�����̃X�s�[�h
	int m_iAnimCount;		//�A�j���[�V�����J�E���g
	bool m_isActive;		//�\���t���O
public:
	D3D11_SPRITE();
	~D3D11_SPRITE();
	
	static void InitShader(ID3D11DeviceContext* pContext, DWORD width, DWORD height);
	HRESULT Init(WCHAR *filepass, D3DXVECTOR2 size, int animSpeed);
	void Render(D3DXVECTOR3 pos,D3DXVECTOR2 scale,D3DXVECTOR3 rot);
	static void SetCamera(D3DXMATRIX mView, D3DXMATRIX mProj);

	
};