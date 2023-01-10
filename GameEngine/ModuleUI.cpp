#include "Application.h"
#include "ModuleUI.h"
#include "ModuleMesh.h"
#include "ComponentMesh.h"
#include "Primitives.h"
#include "ComponentCamera.h"

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
	Application::GetInstance()->meshRenderer->LoadMesh(m);
	return GO;
}

