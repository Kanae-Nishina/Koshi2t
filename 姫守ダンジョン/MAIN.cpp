//
//	@file	MAIN.cpp
//	@brief	メインクラス

#include "MAIN.h"
//グローバル変数
MAIN* g_pMain = NULL;


//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//
//
//アプリケーションのエントリー関数 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	g_pMain = new MAIN;
	if (g_pMain != NULL)
	{
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME)))
		{
			//g_pMain->CreateConsoleWindow();
			if (SUCCEEDED(g_pMain->InitD3D()))
			{
				g_pMain->Loop();
			}
		}
		//アプリ終了
		//g_pMain->CloseConsoleWindow();
		g_pMain->DestroyD3D();
		delete g_pMain;
	}
	return 0;
}
//
//
//OSから見たウィンドウプロシージャー（実際の処理はMAINクラスのプロシージャーで処理）
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);
}
//
//
//ウィンドウ作成
HRESULT MAIN::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
{
	// ウィンドウの定義
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	m_hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);
	if (!m_hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}
//
//
//ウィンドウプロシージャー
LRESULT MAIN::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE://ESCキーで修了
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
//
//
//メッセージループとアプリケーション処理の入り口
void MAIN::Loop()
{


	//初期化
	//スタティックメッシュ
	CD3DXMESH::InitShader(m_hWnd, m_pDevice, m_pDeviceContext);
	//スキンメッシュ
	CD3DXSKINMESH::Init(m_hWnd, m_pDevice, m_pDeviceContext);
	//スプライト
	D3D11_SPRITE::InitShader(m_pDeviceContext,WINDOW_WIDTH,WINDOW_HEIGHT);
	//UI
	TD_Graphics::InitShader(m_pDeviceContext);
	//サウンド
	Sound::getInstance().Run();
	//エフェクト
	Effect::getInstance().EffectInit(m_hWnd, m_pDevice, m_pDeviceContext/*,m_pSwapChain, m_pBackBuffer_TexRTV, m_pBackBuffer_DSTexDSV, m_pBackBuffer_DSTex*/);
	////キャラクターデータ・モデルの読み込み
	//CharactorCreator::LoadModel();

	//シーンマネージャ
	root_ = new SceneRoot;
	root_->Init();

	// メッセージループ
	MSG msg = { 0 };
	start = timeGetTime();
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//アプリケーションの処理はここから飛ぶ。
			App();

			//FPS調整
			while (timeGetTime() - start < 1000 / FPS)
			{
				Sleep(1);
			}
			start = timeGetTime();
		}
	}
	//アプリケーションの終了
}
//
//
//アプリケーション処理。アプリのメイン関数。
void MAIN::App()
{
	Update();
	Render();
}
//
//
//
HRESULT MAIN::InitD3D()
{
	// デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW_WIDTH;
	sd.BufferDesc.Height = WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice,
		pFeatureLevel, &m_pDeviceContext)))
	{
		return FALSE;
	}
	//各種テクスチャーと、それに付帯する各種ビューを作成

	//バックバッファーテクスチャーを取得（既にあるので作成ではない）
	ID3D11Texture2D *pBackBuffer_Tex;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);
	//そのテクスチャーに対しレンダーターゲットビュー(RTV)を作成
	m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL, &m_pBackBuffer_TexRTV);
	SAFE_RELEASE(pBackBuffer_Tex);

	//デプスステンシルビュー用のテクスチャーを作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINDOW_WIDTH;
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pBackBuffer_DSTex);
	//そのテクスチャーに対しデプスステンシルビュー(DSV)を作成
	m_pDevice->CreateDepthStencilView(m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer_TexRTV, m_pBackBuffer_DSTexDSV);
	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);
	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr = NULL;
	m_pDevice->CreateRasterizerState(&rdc, &pIr);
	m_pDeviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);

	//初期化
	D3DXVECTOR4 vColor(1, 1, 1, 1);
	D3D11_TEXT::Init(m_pDeviceContext, WINDOW_WIDTH, WINDOW_HEIGHT, 100, vColor);
	//mainScene_ = new Main_Scene;
	//mainScene_->DebugInit(m_pDeviceContext);
	return S_OK;
}
//
//
//
void MAIN::DestroyD3D()
{
	//delete camera_;
	//camera_ = nullptr;
	//CharactorCreator::Destroy();
	root_->Destroy();
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDevice);
}

//
//
//更新処理
void MAIN::Update()
{
	//camera_->Update();
	//mainScene_->Update();
	scene_ = nullptr;
	scene_ = root_->Update(root_);
}

//
//
//シーンを画面にレンダリング
void MAIN::Render()
{
	//scene_ = nullptr;
	//scene_ = root_->Update(root_);


	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,0,0 };// クリア色作成　RGBAの順
	m_pDeviceContext->ClearRenderTargetView(m_pBackBuffer_TexRTV, ClearColor);//画面クリア
	m_pDeviceContext->ClearDepthStencilView(m_pBackBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//深度バッファクリア


	CD3DXMESH::SetCamera(Camera::mView_, Camera::mProj_);
	CD3DXSKINMESH::SetCamera(Camera::mView_, Camera::mProj_);
	TD_Graphics::SetCamera(Camera::mView_, Camera::mProj_);
	D3D11_SPRITE::SetCamera(Camera::mView_, Camera::mProj_);
	D3D11_TEXT::SetCamera(Camera::mView_, Camera::mProj_);
	/*Camera* camera_ = new Camera;
	Effect::getInstance().SetCamera(camera_->movePow_, camera_->gazePoint_);*/

	scene_->Render();

	//画面更新（バックバッファをフロントバッファに）
	m_pSwapChain->Present(0, 0);

	/*char Str[512];
	sprintf(Str, "fps:%f", start);
	SetWindowTextA(m_hWnd, Str);*/

	//FPS計算表示
	static DWORD time = 0;
	static int frame = 0;
	frame++;
	char str[50];
	sprintf(str, "fps=%d", frame);
	if (timeGetTime() - time>1000)
	{
		time = timeGetTime();
		frame = 0;
		SetWindowTextA(m_hWnd, str);
	}
}