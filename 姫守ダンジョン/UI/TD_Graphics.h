//
//	@file	TD_Graphics.h
//	@brief	UI�`��N���X
//	@date	4���쐬�A1���啝�ύX
//	@author	�g�z��R(�p��)
//	@note	���ɗp�ӂ���Ă����N���X��啝�ɕύX(�m�ȍ��c)

#pragma once
#include "../Origin.h"
#include "D3D11_SPRITE.h"

struct SIMPLESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX mWVP;
	D3DXVECTOR4 vColor;
	D3DXVECTOR4 fAlpha;
};
//
//
struct SimpleVertex
{
	D3DXVECTOR3 Pos; //�ʒu
	D3DXVECTOR2 vTex; //�e�N�X�`���[���W
};
//
//
struct GrapRect
{
	GrapRect(float top, float bottom, float left, float right){
		m_top = top;
		m_bottom = bottom;
		m_left = left;
		m_right = right;
	}
	~GrapRect(){}

	float m_top;
	float m_bottom;
	float m_left;
	float m_right;
};
//
//
class TD_Graphics
{
public:
	TD_Graphics();
	~TD_Graphics();

	static HRESULT InitShader(ID3D11DeviceContext* pContext);
	static void SetCamera(D3DXMATRIX view, D3DXMATRIX proj);


	// @param (textname)	texture�p�X
	// @param (texsize)     �摜�T�C�Y
	// @param (vColor)		�F
	// @param (_Rect)		���N�g
	HRESULT Init(LPCWSTR texname,D3DXVECTOR2 texsize, D3DXVECTOR4 vColor, GrapRect _Rect);


	// @param (pos)		�\�����W
	// @param (scale)	�g��{��
	// @param (flg)		���f���Ƃ̑O��֌W(�^�Ȃ烂�f�����O)
	void	Render(D3DXVECTOR2 pos,D3DXVECTOR2 scale,bool flg);

	void SetAlfa(float alpha);

private:
	static ID3D11Device*				m_pDevice;
	static ID3D11DeviceContext*			m_pDeviceContext;
	static ID3D11SamplerState*			m_pSampleLinear;
	static ID3D11VertexShader*			m_pVertexShader;
	static ID3D11PixelShader*			m_pPixelShader;
	static ID3D11InputLayout*			m_pVertexLayout;
	static ID3D11Buffer*				m_pConstantBuffer;
	static ID3D11BlendState*			m_pBlendState;
	static D3D11_BLEND_DESC				dd;
	static D3DXMATRIX					m_mView;
	static D3DXMATRIX					m_mProj;

	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11ShaderResourceView*	m_pAsciiTexture;
	ID3D11Buffer*				m_RectBuffer;
	float						m_fScale;				//25pixel��� 25pixel=1.0f
	float						m_fAlpha;
	int							m_iAnimSpeed;
	int							m_iAnimCount;
	D3DXVECTOR4					m_vColor;
	D3DXVECTOR2					m_Size;

	static void	StopBlendState() {
		dd.RenderTarget[0].BlendEnable = false;
		m_pDevice->CreateBlendState(&dd, &m_pBlendState);
	}
	static void StartBlendState() {
		dd.RenderTarget[0].BlendEnable = true;
		m_pDevice->CreateBlendState(&dd, &m_pBlendState);
	}
};