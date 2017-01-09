#pragma once
#include <iostream>
#include <map>
#include <string>
#include "./../SceneParts/Scene.h"
#include "./../SceneManager/SceneRoot.h"
#include "./../SceneParts/CharactorSelection_Scene.h"
#include "./../../Mesh/CD3DXSKINMESH.h"
#include "./../../Charactor/CharactorCreator.h"
#include "./../../Camera.h"

class Title_Scene :public Scene
{
private:

	std::map<std::string, TD_Graphics*> title_UI;
	CD3DXSKINMESH* mesh_sword_;
	CD3DXSKINMESH* mesh_shiled_;
	CD3DXSKINMESH* mesh_bomber_;
	CD3DXSKINMESH* mesh_witch_;
	CD3DXSKINMESH* mesh_princess_;
	CD3DXSKINMESH* mesh_enemy_;

	Camera* camera_;
public:
	Title_Scene();
	~Title_Scene();

	void Init();
	SceneBase* Update(SceneRoot* root);
	void Render();
	void Destroy();
};