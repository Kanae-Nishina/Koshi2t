#include "TD_Graphics.h"

ID3D11Device* TD_Graphics::m_pDevice = nullptr;
ID3D11DeviceContext* TD_Graphics::m_pDeviceContext = nullptr;
ID3D11SamplerState* TD_Graphics::m_pSampleLinear = nullptr;
ID3D11VertexShader* TD_Graphics::m_pVertexShader = nullptr;
ID3D11PixelShader* TD_Graphics::m_pPixelShader = nullptr;
ID3D11InputLayout* TD_Graphics::m_pVertexLayout = nullptr;
ID3D11Buffer* TD_Graphics::m_pConstantBuffer = nullptr;

//=======================================================
//	�R���X�g���N�^
//=======================================================
TD_Graphics::TD_Graphics()
{
	ZeroMemory(this, sizeof(TD_Graphics));
	m_fScale = 1.0f;
	//�J�[�j���O�ʂ��ʂɐݒ�

	m_fKerning[0] = 23;//space
	m_fKerning[1] = 16;//!
	m_fKerning[2] = 19;//"
	m_fKerning[3] = 22;//#
	m_fKerning[4] = 22;//$
	m_fKerning[5] = 23;//%
	m_fKerning[6] = 23;//&
	m_fKerning[7] = 18;//'
	m_fKerning[8] = 16;//(
	m_fKerning[9] = 16;//)
	m_fKerning[10] = 18;//*
	m_fKerning[11] = 20;//+
	m_fKerning[12] = 17;//,
	m_fKerning[13] = 17;//-
	m_fKerning[14] = 16;//.
	m_fKerning[15] = 19;// /
	m_fKerning[16] = 20;//0
	m_fKerning[17] = 19;//1
	m_fKerning[18] = 20;//2
	m_fKerning[19] = 21;//3
	m_fKerning[20] = 20;//4
	m_fKerning[21] = 20;//5
	m_fKerning[22] = 20;//6
	m_fKerning[23] = 20;//7
	m_fKerning[24] = 20;//8
	m_fKerning[25] = 20;//9
	m_fKerning[26] = 16;//:
	m_fKerning[27] = 16;//;
	m_fKerning[28] = 18;//<
	m_fKerning[29] = 20;//=
	m_fKerning[30] = 21;//>
	m_fKerning[31] = 19;//?
	m_fKerning[32] = 22;//@
	m_fKerning[33] = 21;//A
	m_fKerning[34] = 20;//B
	m_fKerning[35] = 20;//C
	m_fKerning[36] = 22;//D
	m_fKerning[37] = 18;//E
	m_fKerning[38] = 21;//F
	m_fKerning[39] = 22;//G
	m_fKerning[40] = 22;//H
	m_fKerning[41] = 16;//I
	m_fKerning[42] = 19;//J
	m_fKerning[43] = 21;//K
	m_fKerning[44] = 23;//L
	m_fKerning[45] = 24;//M
	m_fKerning[46] = 21;//N
	m_fKerning[47] = 23;//O
	m_fKerning[48] = 20;//P
	m_fKerning[49] = 22;//Q
	m_fKerning[50] = 20;//R
	m_fKerning[51] = 19;//S
	m_fKerning[52] = 21;//T
	m_fKerning[53] = 21;//U
	m_fKerning[54] = 24;//V
	m_fKerning[55] = 25;//W
	m_fKerning[56] = 20;//X
	m_fKerning[57] = 20;//Y
	m_fKerning[58] = 20;//Z
	m_fKerning[59] = 15;//[
	m_fKerning[60] = 17;// \/
	m_fKerning[61] = 15;//]
	m_fKerning[62] = 19;//^
	m_fKerning[63] = 21;//_
	m_fKerning[64] = 17;//`
	m_fKerning[65] = 21;//a
	m_fKerning[66] = 21;//b
	m_fKerning[67] = 18;//c
	m_fKerning[68] = 20;//d
	m_fKerning[69] = 19;//e
	m_fKerning[70] = 18;//f
	m_fKerning[71] = 20;//g
	m_fKerning[72] = 18;//h
	m_fKerning[73] = 14;//i
	m_fKerning[74] = 19;//j
	m_fKerning[75] = 21;//k
	m_fKerning[76] = 22;//l
	m_fKerning[77] = 24;//m
	m_fKerning[78] = 20;//n
	m_fKerning[79] = 19;//o
	m_fKerning[80] = 20;//p
	m_fKerning[81] = 19;//q
	m_fKerning[82] = 17;//r
	m_fKerning[83] = 17;//s
	m_fKerning[84] = 19;//t
	m_fKerning[85] = 20;//u
	m_fKerning[86] = 22;//v
	m_fKerning[87] = 22;//w
	m_fKerning[88] = 19;//x
	m_fKerning[89] = 19;//y
	m_fKerning[90] = 19;//z
	m_fKerning[91] = 16;//{
	m_fKerning[92] = 14;//|
	m_fKerning[93] = 18;//}
	m_fKerning[94] = 19;//~

}

//=======================================================
//	�f�X�g���N�^
//=======================================================
TD_Graphics::~TD_Graphics()
{
	for (int i = 0; i<PIC2D_NUM; i++)
		SAFE_RELEASE(m_pAsciiTexture[i]);
}

HRESULT TD_Graphics::InitDevice(ID3D11DeviceContext * pContext)
{
	m_pDeviceContext = pContext;
	m_pDeviceContext->GetDevice(&m_pDevice);

	return S_OK;
}


HRESULT TD_Graphics::Init(LPCWSTR textname, int texnum, D3DXVECTOR2 drawpos, D3DXVECTOR2 texsize, D3DXVECTOR4 vColor, GrapRect _Rect)
{
	//LPCWSTR texturename = textname;
	drawnum = texnum;
	m_fAlpha = vColor.w;
	m_vColor = vColor;
	//m_fScale = texsize / 25.0f;

	for (int i = 0; i<95; i++)
	{
		m_fKerning[i] *= 1.0f;// m_fScale;
	}
	//�f�o�C�X�ƃR���e�L�X�g���R�s�[
	//m_pDeviceContext = pContext;// pContext;
	//m_pDeviceContext->GetDevice(&m_pDevice);
	//�t�H���g���ƂɃN�A�b�h�쐬
	//	float left = 0, top = 0, right = 512, bottom = 128;
	float left = drawpos.x, top = drawpos.y, right = texsize.x + left, bottom = texsize.y + top;
	float dimension = 25.0f / 2.0f;
	int cnt = 0;

	SimpleVertex vertices[] =
	{
		D3DXVECTOR3(left, bottom, 0), D3DXVECTOR2(_Rect.m_left, _Rect.m_bottom),//���_1,
		D3DXVECTOR3(left, top, 0), D3DXVECTOR2(_Rect.m_left, _Rect.m_top),//���_2
		D3DXVECTOR3(right, bottom, 0), D3DXVECTOR2(_Rect.m_right, _Rect.m_bottom), //���_3
		D3DXVECTOR3(right, top, 0), D3DXVECTOR2(_Rect.m_right, _Rect.m_top), //���_4
	};

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer[cnt])))
	{
		return E_FAIL;
	}
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
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
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

	InitTex(textname, texnum, drawpos, texsize, vColor);
	return S_OK;
}

HRESULT TD_Graphics::InitTex(LPCWSTR textname, int texnum, D3DXVECTOR2 drawpos, D3DXVECTOR2 texsize, D3DXVECTOR4 vColor)
{

	LPCWSTR texturename = textname;
	//�t�H���g�̃e�N�X�`���[���쐬
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_pDevice, texturename/*L"Sucore_Waku.png"*/, NULL, NULL, &m_pAsciiTexture[drawnum], NULL)))
	{
		return E_FAIL;
	}
}
//
//
void TD_Graphics::Render(char* text, int dnum, int x, int y)
{
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
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pAsciiTexture[dnum]);

	//render
	RenderFont(0, x, y);

}
//
//
//
void TD_Graphics::RenderFont(int FontIndex, int x, int y)
{
	//���[���h�ϊ�
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixTranslation(&mWorld, x, y, -100);
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
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
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer[FontIndex], &stride, &offset);

	//�����F
	UINT ColorKey = 0xffffffff;
	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, ColorKey);
	m_pDeviceContext->Draw(4, 0);
}

void TD_Graphics::SetBlend_Desc()
{
	//�����F�ݒ�
	dd.IndependentBlendEnable = true;
	dd.AlphaToCoverageEnable = false;

	dd.RenderTarget[0].BlendEnable = true;
	dd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	dd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	dd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	dd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	dd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	dd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	dd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&dd, &m_pBlendState)))
	{
		return;
	}
}