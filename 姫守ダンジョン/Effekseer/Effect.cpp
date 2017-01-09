#include "Effect.h"

map<string, int>				effect_;

::Effekseer::Manager* Effect::g_manager = nullptr;
::EffekseerRenderer::Renderer* Effect::g_renderer = nullptr;

ID3D11Device* Effect::g_device = nullptr;
ID3D11DeviceContext* Effect::g_context = nullptr;


//
//	@brief	�R���X�g���N�^
Effect::Effect()
{
	ZeroMemory(this, sizeof(Effect));
	for (int i = 0; i < MAX; i++)
	{
		g_handle[i] = -1;
	}

}

//
//	@brief	�f�X�g���N�^
Effect::~Effect()
{
	/*for (int i = 0; i < g_effect.size(); i++)
	{
	ES_SAFE_RELEASE(g_effect[0]);
	}*/

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	g_renderer->Destory();

	ES_SAFE_RELEASE(g_context);
	ES_SAFE_RELEASE(g_device);
}

//
//	@brief	������
void Effect::EffectInit(HWND whand, ID3D11Device* device, ID3D11DeviceContext* context)
{
	g_device = device;
	g_context = context;
	HWND g_window_handle = whand;
	static IDXGIDevice1*				g_dxgiDevice = NULL;
	static IDXGIAdapter*				g_adapter = NULL;
	static IDXGIFactory*				g_dxgiFactory = NULL;
	static ID3D11Texture2D*				g_depthBuffer = NULL;

	static IDXGISwapChain* g_swapChain = NULL;
	static ID3D11RenderTargetView* g_renderTargetView = NULL;
	static ID3D11DepthStencilView* g_depthStencilView = NULL;
	static ID3D11Texture2D* g_backBuffer = NULL;
	//////

	// DirectX11�̏��������s��
	if (FAILED(g_device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&g_dxgiDevice)))
	{
		return;
	}

	if (FAILED(g_dxgiDevice->GetAdapter(&g_adapter)))
	{
		return;
	}

	g_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&g_dxgiFactory);
	if (g_dxgiFactory == NULL)
	{
		return;
	}

	DXGI_SWAP_CHAIN_DESC hDXGISwapChainDesc;
	hDXGISwapChainDesc.BufferDesc.Width = WINDOW_WIDTH;
	hDXGISwapChainDesc.BufferDesc.Height = WINDOW_HEIGHT;
	hDXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	hDXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	hDXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	hDXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	hDXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	hDXGISwapChainDesc.SampleDesc.Count = 1;
	hDXGISwapChainDesc.SampleDesc.Quality = 0;
	hDXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	hDXGISwapChainDesc.BufferCount = 1;
	hDXGISwapChainDesc.OutputWindow = (HWND)g_window_handle;
	hDXGISwapChainDesc.Windowed = TRUE;
	hDXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	hDXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(g_dxgiFactory->CreateSwapChain(g_device, &hDXGISwapChainDesc, &g_swapChain)))
	{
		return;
	}

	if (FAILED(g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&g_backBuffer)))
	{
		return;
	}

	if (FAILED(g_device->CreateRenderTargetView(g_backBuffer, NULL, &g_renderTargetView)))
	{
		return;
	}

	D3D11_TEXTURE2D_DESC hTexture2dDesc;
	hTexture2dDesc.Width = hDXGISwapChainDesc.BufferDesc.Width;
	hTexture2dDesc.Height = hDXGISwapChainDesc.BufferDesc.Height;
	hTexture2dDesc.MipLevels = 1;
	hTexture2dDesc.ArraySize = 1;
	hTexture2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	hTexture2dDesc.SampleDesc = hDXGISwapChainDesc.SampleDesc;
	hTexture2dDesc.Usage = D3D11_USAGE_DEFAULT;
	hTexture2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	hTexture2dDesc.CPUAccessFlags = 0;
	hTexture2dDesc.MiscFlags = 0;
	if (FAILED(g_device->CreateTexture2D(&hTexture2dDesc, NULL, &g_depthBuffer)))
	{
		return;
	}

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (float)WINDOW_WIDTH;
	vp.Height = (float)WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_context->RSSetViewports(1, &vp);


	//�ǂݍ���
	Set();
}

//
//	@brief	�`�揀��
void Effect::Set()
{
	// �`��p�C���X�^���X�̐���
	g_renderer = ::EffekseerRendererDX11::Renderer::Create(g_device, g_context, 2000);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(2000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());

	// �G�t�F�N�g�̓Ǎ�
	EffectSet();
	//effect_["smork"] = LoadEffect((const EFK_CHAR*)L"Effekseer/Effects/��/smork.efk");
	//effect_["smork"] = LoadEffect((const EFK_CHAR*)L"Effekseer/EffectsMaterial/bi-m2.efk");

	//g_handle = g_manager->Play(g_effect, 0, 0, 0);
}

//
//	@brief	�G�t�F�N�g�ǂݍ���
void Effect::EffectSet()
{
	//�S��
	effect_["charge1"] = LoadEffect((const EFK_CHAR*)L"Effekseer/Effects/�S��/charge1.efk");
	effect_["charge2"] = LoadEffect((const EFK_CHAR*)L"Effekseer/Effects/�S��/charge2.efk");

	//���m

	//���m
	effect_["smork"] = LoadEffect((const EFK_CHAR*)L"Effekseer/Effects/���m/smork.efk");

	//���e�m
	effect_["explosion"] = LoadEffect((const EFK_CHAR*)L"Effekseer/Effects/���e�m/explosion.efk");

	//�����m
	//effect_["beam1"] = LoadEffect((const EFK_CHAR*)L"Effekseer/Effects/�����m/beam1.efk");

	effect_["beam2"] = LoadEffect((const EFK_CHAR*)L"Effekseer/Effects/�����m/bi-m2.efk");

	//�P

	//
}

//
//	@brief	�G�t�F�N�g�̃��[�h
int Effect::LoadEffect(const EFK_CHAR* path)
{
	assert(Effekseer::Effect::Create(g_manager, path) != NULL);
	static int no = -1;
	++no;
	g_effect[no] = Effekseer::Effect::Create(g_manager, path);
	return no;
}

//
//	@brief			�J�����Z�b�g
//	@param(pos)		�J�����̎��_���W
//	@param(look)	�J�����̒����_���W
void Effect::SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look)
{
	Effekseer::Vector3D g_position = ::Effekseer::Vector3D(pos.x, pos.y, pos.z);
	const Effekseer::Vector3D g_at = ::Effekseer::Vector3D(look.x, look.y, look.z);
	const Effekseer::Matrix44 m_View = ::Effekseer::Matrix44().LookAtLH(g_position, g_at, ::Effekseer::Vector3D(0, 1, 0));
	const Effekseer::Matrix44 m_Proj = ::Effekseer::Matrix44().PerspectiveFovLH(D3DX_PI / 6, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0f);

	// ���e�s���ݒ�
	g_renderer->SetProjectionMatrix(m_Proj);

	// �J�����s���ݒ�
	g_renderer->SetCameraMatrix(m_View);

}

//
//	@brief			�`��J�n
//	@param (pos)	�`����W
void Effect::Effect_Play(string name, D3DXVECTOR3 pos)
{
	g_handle[effect_[name]] = g_manager->Play(g_effect[effect_[name]], pos.x, pos.y, pos.z);
}

//
//	@brief			�`��I��
//	@param (name)	�`����I������G�t�F�N�g��
void Effect::Effect_Stop(string name)
{
	g_manager->StopEffect(g_handle[effect_[name]]);
}

//
//	@brief			�X�P�[���̐ݒ�
//	@param (name)	�X�P�[����ݒ肷��G�t�F�N�g
//	@param (scale)	�g�嗦
void Effect::SetScale(string name, float scale)
{
	g_manager->SetScale(g_handle[effect_[name]], scale, scale, scale);
}

//
//	@brief			�X�V
//	@param(name)	�X�V����G�t�F�N�g��
//	@param(pos)		�`����W
void Effect::Update(string name, D3DXVECTOR3 pos)
{
	//�@���W�ݒ�
	::Effekseer::Vector3D e_pos(pos.x, pos.y, pos.z);
	//�@�ړ��X�V
	g_manager->SetLocation(g_handle[effect_[name]], e_pos);
	// �G�t�F�N�g�̍X�V�������s��
	g_manager->Update();
}

void Effect::Draw()
{
	// �G�t�F�N�g�̕`��J�n�������s���B
	g_renderer->BeginRendering();

	// �G�t�F�N�g�̕`����s���B
	g_manager->Draw();

	// �G�t�F�N�g�̕`��I���������s���B
	g_renderer->EndRendering();
}
