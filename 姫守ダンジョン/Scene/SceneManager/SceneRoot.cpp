#include "./SceneRoot.h"

Scene* SceneRoot::beforeScene_ = nullptr;
Scene* SceneRoot::nextScene_ = nullptr;
bool SceneRoot::loadFlg_=false;

SceneRoot::SceneRoot()
	:scene_(nullptr)
	//,mode_(kNone)
{
}

SceneRoot::~SceneRoot()
{
}


void SceneRoot::Init()
{
	//std::cout << "SceneRoot::Startup()" << std::endl;

	//scene_ = new SceneTitle();

	//loadScene_ = new Load_Scene;
	scene_ = new Title_Scene;
	scene_->Init();
}

void SceneRoot::Destroy()
{
	//std::cout << "SceneRoot::Shutdown()" << std::endl;
	//delete loadScene_;
	delete scene_;
	scene_ = nullptr;
}




SceneBase* SceneRoot::Update(SceneBase* scene)
{
	//std::cout << "SceneRoot::Update(SceneBase)" << std::endl;

	//if (getchar() == 'q')
	//{
	//	return nullptr;
	//}

	//�V�[���̎��s
	SceneBase* next = scene_->Update(this);

	//�߂�l�����݂̃V�[���ƈقȂ��Ă���΃V�[���؂�ւ�����
	if (next != scene_)
	{
		// beforeScene_ = scene_;

		Scene* casted = dynamic_cast<Scene*>(next);
		assert(casted);

		scene_->Destroy();
		delete scene_;
		scene_ = nullptr;
		
		//next = loadScene_;
		scene_ = new Load_Scene;
		//scene_ = new Load_Scene;
		scene_->Init();
		nextScene_ = casted;
		//next->Init();
		
		//	�ʃX���b�h�N��
		_beginthreadex(
			NULL, //�Z�L�����e�B����
			0, //�X�^�b�N�T�C�Y
			ThreadFunc, //�X���b�h�֐�
			NULL, //�X���b�h�֐��ɓn������
			0, //�쐬�I�v�V����(0�܂���CREATE_SUSPENDED)
			NULL);//�X���b�hID
	}
	if (loadFlg_)
	{
		scene_->Destroy();
		delete scene_;
		scene_ = nullptr;

		scene_ = nextScene_;
		loadFlg_ = false;
	}

	return this;
}

void SceneRoot::Render()
{
	scene_->Render();
}

void SceneRoot::Load()
{
	//beforeScene_->Destroy();
	//delete beforeScene_;
	nextScene_->Init();
	loadFlg_ = true;
}

unsigned int WINAPI SceneRoot::ThreadFunc(LPVOID arg)
{
	Load();
	return 0;
}