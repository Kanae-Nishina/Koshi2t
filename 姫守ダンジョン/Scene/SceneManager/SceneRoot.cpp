#include "./SceneRoot.h"
#include "./../SceneParts/Main_Scene.h"

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

	scene_ = new Title_Scene;
	scene_->Init();
}

void SceneRoot::Destroy()
{
	//std::cout << "SceneRoot::Shutdown()" << std::endl;
	delete scene_;
	//scene_ = nullptr;
}

SceneBase* SceneRoot::Update(SceneBase* scene)
{
	//std::cout << "SceneRoot::Update(SceneBase)" << std::endl;

	if (getchar() == 'q')
	{
		return nullptr;
	}

	//�V�[���̎��s
	SceneBase* next = scene_->Update(this);

	//�߂�l�����݂̃V�[���ƈقȂ��Ă���΃V�[���؂�ւ�����
	if (next != scene_)
	{
		Scene* casted = dynamic_cast<Scene*>(next);
		assert(casted);

		scene_->Destroy();
		delete scene_;

		scene_ = casted;
		scene_->Init();
	}
	return this;
}

void SceneRoot::Render()
{
	scene_->Render();
}