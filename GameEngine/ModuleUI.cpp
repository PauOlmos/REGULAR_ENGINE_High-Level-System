#include "Application.h"
#include "ModuleUI.h"
#include "ModuleMesh.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "Primitives.h"
#include "ComponentCamera.h"
#include "Transform.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	UICam = new CameraComponent(ComponentType::UICAMERA);
	UICam->frustum.pos = float3( 0,0,0 );
	CreateUICrosshair(UIType::NORMAL);
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUI::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	return UPDATE_CONTINUE;
}

GameObject* ModuleUI::CreateUI(UIType GOtype)
{
	GameObject* GO = new GameObject();
	GO->type = GOtype::UI;
	ComponentMesh* cm = new ComponentMesh();
	ComponentTexture* ct = new ComponentTexture();
	//ct->SetTexture("Assets\crosshair.png");
	Mesh* m = nullptr;

	switch (GOtype) {
	case UIType::NORMAL:
		GO->name = "Cube";
		m = Primitives::CreateCube();
		break;
	}

	m->myGameObject = GO;
	//Create AABB box
	m->InitAABB();
	m->Mtype = MESHtype::UI;
	cm->meshes.push_back(m);
	GO->AddComponent(cm);
	GO->AddComponent(ct);
	Application::GetInstance()->meshRenderer->LoadMesh(m);
	return GO;
}

GameObject* ModuleUI::CreateUICrosshair(UIType GOtype)
{
	GameObject* GO = new GameObject();
	GO->type = GOtype::UI;
	ComponentMesh* cm = new ComponentMesh();
	ComponentTexture* ct = new ComponentTexture();
	//ct->SetTexture("Assets\crosshair.png");
	Mesh* m = nullptr;

	switch (GOtype) {
	case UIType::NORMAL:
		GO->name = "UI Plane";
		m = Primitives::CreateCube();
		break;
	}

	m->myGameObject = GO;

	//Create AABB box
	m->InitAABB();
	m->Mtype = MESHtype::UI;
	cm->meshes.push_back(m);
	GO->AddComponent(cm);
	GO->AddComponent(ct);
	GO->transform->setPosition({ 0,0,0 });
	GO->transform->setScale({ 0.1,0.1,1 });
	Application::GetInstance()->meshRenderer->LoadMesh(m);
	return GO;
}

