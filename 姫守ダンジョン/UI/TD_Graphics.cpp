#include "TD_Graphics.h"

ID3D11Device* TD_Graphics::m_pDevice = nullptr;
ID3D11DeviceContext* TD_Graphics::m_pDeviceContext = nullptr;
ID3D11SamplerState* TD_Graphics::m_pSampleLinear = nullptr;
ID3D11VertexShader* TD_Graphics::m_pVertexShader = nullptr;
ID3D11PixelShader* TD_Graphics::m_pPixelShader = nullptr;
ID3D11InputLayout* TD_Graphics::m_pVertexLayout = nullptr;
ID3D11Buffer* TD_Graphics::m_pConstantBuffer = nullptr;
ID3D11BlendState* TD_Graphics::m_pBlendState;
D3D11_BLEND_DESC TD_Graphics::dd;
//ID3D11Buffer* TD_Graphics::m_pVertexBuffer/*[100]*/;
D3DXMATRIX TD_Graphics::m_mView;
D3DXMATRIX TD_Graphics::m_mProj;

//=======================================================
//	�R���X�g���N�^
//=======================================================
TD_Graphics::TD_Graphics()
{
	ZeroMemory(this, sizeof(TD_Graphics));
	m_fScale = 1.0f;
}

//=======================================================
//	�f�X�g���N�^
//=======================================================
TD_Graphics::~TD_Graphics()
{
	SAFE_RELEASE(m_pAsciiTexture);
}

HRESULT TD_Graphics::Init(LPCWSTR textname, /*int texnum, */D3DXVECTOR2 drawpos, D3DXVECTOR2 texsize, D3DXVECTOR4 vColor, GrapRect _Rect)
{
	m_fAlpha = vColor.w;
	m_vColor = vColor;

	float left = drawpos.x, top = drawpos.y, right = texsize.x + left, bottom = texsize.y + top;
	m_Size = texsize;
	GrapRect rect = GrapRect(0.0f, 0.0f, 1.0f / m_Size.x, 1.0f / m_Size.y);
	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(left, bottom, 0), D3DXVECTOR2(_Rect.m_left, _Rect.m_bottom),//���_1,
		D3DXVECTOR3(left, top, 0), D3DXVECTOR2(_Rect.m_left, _Rect.m_top),//���_2
		D3DXVECTOR3(right, bottom, 0), D3DXVECTOR2(_Rect.m_right, _Rect.m_bottom), //���_3
		D3DXVECTOR3(right, top, 0), D3DXVECTOR2(_Rect.m_right, _Rect.m_top), //���_4
	};
	//SimpleVertex vertices[] =
	//{
	//	D3DXVECTOR3(0, bottom, 0), D3DXVECTOR2(rect.m_left, rect.m_bottom),//���_1,
	//	D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(rect.m_left, rect.m_top),//���_2
	//	D3DXVECTOR3(right, bottom, 0), D3DXVECTOR2(rect.m_right, rect.m_bottom), //���_3
	//	D3DXVECTOR3(right, 0, 0), D3DXVECTOR2(rect.m_right, rect.m_top), //���_4
	//};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	ID3D11Device* device = m_pDevice;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	LPCWSTR texturename = textname;
	//�e�N�X�`���[���쐬
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(device, texturename, NULL, NULL, &m_pAsciiTexture, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT TD_Graphics::InitShader(ID3D11DeviceContext * pContext)
{
	m_pDeviceContext = pContext;
	m_pDeviceContext->GetDevice(&m_pDevice);

	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);

	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(L"./UI/D3D11_TEXT.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(m_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
		return FALSE;
	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(L"./UI/D3D11_TEXT.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &pCompiledShader, &pErrors, NULL)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//�R���X�^���g�o�b�t�@�[�쐬�@�����ł͕ϊ��s��n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.ByteWidth = sizeof(SPRITE_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}

	//�����F�ݒ�
	D3D11_BLEND_DESC dd;
	ZeroMemory(&dd, sizeof(D3D11_BLEND_DESC));
	dd.IndependentBlendEnable = false;
	dd.AlphaToCoverageEnable = false;
	dd.RenderTarget[0].BlendEnable = true;
	dd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	dd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	dd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	dd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	dd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	dd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	dd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&dd, &m_pBlendState)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//
//
void TD_Graphics::Render(D3DXVECTOR2 pos, D3DXVECTOR2 scale, bool flg)
{
	//�g�|���W�[
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//�g�p����V�F�[�_�[�̓o�^
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pAsciiTexture);

	//���[���h�ϊ�
	float z = 0;
	if (flg)
	{
		z = -1;
	}
	D3DXMATRIX mWorld, mTran, mScale;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixTranslation(&mTran, pos.x, pos.y, z);
	//�X�P�[���ϊ�
	//D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling(&mScale, scale.x, scale.y, 1);
	mWorld = mScale*mTran;
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	SPRITE_CONSTANT_BUFFER cb;
	m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	//���[���h�A�J�����A�ˉe�s���n��
	D3DXMATRIX m = mWorld*m_mView*m_mProj;
	D3DXMatrixTranspose(&m, &m);
	cb.mWVP = m;
	//�J���[��n��
	cb.vColor = m_vColor;
	//�����x��n��
	cb.fAlpha.x = m_fAlpha;

	memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
	m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//�����F
	UINT ColorKey = 0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, ColorKey);
	m_pDeviceContext->Draw(4, 0);
}

void TD_Graphics::AnimRender(D3DXVECTOR2 pos, D3DXVECTOR2 scale, bool flg, int animSpeed)
{
	//�g�|���W�[
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//�g�p����V�F�[�_�[�̓o�^
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pAsciiTexture);

	//���[���h�ϊ�
	float z = 0;
	if (flg)
	{
		z = -1;
	}
	D3DXMATRIX mWorld, mTran, mScale;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixTranslation(&mTran, pos.x, pos.y, z);
	//�X�P�[���ϊ�
	//D3DXMatrixIdentity(&mScale);
	D3DXMatrixScaling(&mScale, scale.x, scale.y, 1);
	mWorld = mScale*mTran;

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	SPRITE_CONSTANT_BUFFER cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n��
		D3DXMATRIX m = mWorld*m_mView*m_mProj;
		D3DXMatrixTranspose(&m, &m);
		cb.mWVP = m;
		//�J���[��n��
		cb.vColor = m_vColor;
		//�����x��n��
		cb.fAlpha.x = m_fAlpha;

		//�e�N�X�`���[�X�N���[���̑�����n��
		static D3DXVECTOR2 TexScroll(0, 0);
		static int count = 0;
		static int m_AnimCount = 0;
		int m_AnimSpeed = animSpeed;
		if (count < m_AnimSpeed) count++;
		if (count >= m_AnimSpeed)
		{
			TexScroll.x += 1.0f / m_Size.x;
			count = 0;
			m_AnimCount++;
			if ((m_AnimCount % (int)m_Size.x) == 0)
			{
				TexScroll.y += 1.0f / m_Size.y;
				TexScroll.x = 0.0f;
			}
			if ((m_AnimCount % (int)(m_Size.x * m_Size.y)) == 0)
			{
				m_AnimCount = 0;
				TexScroll.x = 0.0f;
				TexScroll.y = 0.0f;
			}
		}
		cb.TexScroll = D3DXVECTOR4(TexScroll.x, TexScroll.y, 0, 0);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//�����F
	UINT ColorKey = 0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, ColorKey);
	m_pDeviceContext->Draw(4, 0);
}

void TD_Graphics::SetCamera(D3DXMATRIX view, D3DXMATRIX proj)
{
	m_mView = view;
	m_mProj = proj;

	StartBlendState();//�u�����h��L����

	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -1); //�J�����i���_�j�ʒu
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//�����ʒu
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu
	D3DXMatrixLookAtLH(&m_mView, &vEyePt, &vLookatPt, &vUpVec);

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DMATRIX mOtho = {
		2.0f / (float)(WINDOW_WIDTH), 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f / (float)(WINDOW_HEIGHT), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	};
	m_mProj = mOtho;

}