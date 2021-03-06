#include "Load_Scene.h"

Load_Scene::Load_Scene()
{
	loading_UI = new D3D11_SPRITE;
	descriptionUI_ = new TD_Graphics;
	/*for (int i = 0; i < LOADUI_SPRITE;i++)
	{
		loadingUI_[i] = new TD_Graphics;
	}*/
	debugText_ = new D3D11_TEXT;
	camera_ = new Camera;
}

Load_Scene::~Load_Scene()
{
	delete loading_UI;
	loading_UI = nullptr;
	delete descriptionUI_;
	descriptionUI_ = nullptr;
	/*for (int i = 0; i < LOADUI_SPRITE; i++)
	{
		delete loadingUI_[i];
		loadingUI_[i] = nullptr;
	}*/
	delete camera_;
	camera_ = nullptr;
}

void Load_Scene::Init()
{
	//loading_UI->Init(L"./UI/UI_Tex/lord.png", /*0, */D3DXVECTOR2(0, 0), D3DXVECTOR2(16369, 255), D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), GrapRect(0.0f, 1.0f, 0.0f, 1.0f));
	//loading_UI->Init(D3DXVECTOR4(1.0, 1.0, 1.0, 1.0), true, L"./UI/UI_Tex/lord.png", D3DXVECTOR2(8, 2), 3);
	loading_UI->Init(L"./UI/UI_Tex/lord.png", D3DXVECTOR2(13, 1), 10);
	/*float x = 1 / LOADUI_SPRITE;
	float xSize = 16319 / LOADUI_SPRITE;
	for (int i = 0; i < LOADUI_SPRITE;i++)
	{
		descriptionUI_->Init(L"./UI/UI_Tex/lord.png", D3DXVECTOR2(0, 0), D3DXVECTOR2(xSize, 255), D3DXVECTOR4(1, 1, 1, 1), GrapRect(0, 1, 0+i*x, 1+i*x));
	}*/
	descriptionUI_->Init(L"./UI/UI_Tex/loadscene.png",D3DXVECTOR2(0,0), D3DXVECTOR2(WINDOW_WIDTH, WINDOW_HEIGHT), D3DXVECTOR4(1,1,1,1),GrapRect(0,1,0,1));
	camera_->gazePoint_ = D3DXVECTOR3(0, 0, -32);
	camera_->movePow_ = D3DXVECTOR3(-7.2, 6.4, -42);
	uiAnimCount_ = 0;
}

void Load_Scene::Destroy()
{

}

SceneBase* Load_Scene::Update(SceneRoot* root)
{
	SceneBase* next = this;

	return next;
}

void Load_Scene::Render()
{

	static D3DXVECTOR3 pos(0, 0, 0);
	D3DXVECTOR2 scale(0.1, 0.05);
	D3DXVECTOR3 rot(0,D3DX_PI,0);
	float speed = 0.001;
	camera_->movePow_.x += (GetKeyState(VK_LEFT) & 0x80)*speed + -(GetKeyState(VK_RIGHT) & 0x80)*speed;
	camera_->movePow_.y += (GetKeyState('W') & 0x80)*speed + -(GetKeyState('S') & 0x80)*speed;
	camera_->movePow_.z += (GetKeyState(VK_UP) & 0x80)*speed + -(GetKeyState(VK_DOWN) & 0x80)*speed;
	camera_->gazePoint_ = camera_->movePow_;
	camera_->gazePoint_.z = camera_->movePow_.z + 10;
	loading_UI->Render(pos, scale, rot);

	descriptionUI_->Render(D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), false);

	//++uiAnimCount_;
	//loadingUI_[0]->Render(D3DXVECTOR2(0, 0), D3DXVECTOR2(0.5, 1), true);


	camera_->Render();
#ifdef _DEBUG
	char str[256];
	sprintf(str, "pos.x:%f pos.y:%f pos.z:%f", camera_->movePow_.x, camera_->movePow_.y, camera_->movePow_.z);
	debugText_->Render(str, 0, 50);
#endif // _DEBUG


}
