#include "Application.h"
#include "ModuleUI.h"
#include "ModuleMesh.h"
#include "ComponentMesh.h"
#include "Primitives.h"

ModuleUI::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	UICam = new UICameraComponent();
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

	Application::GetInstance()->meshRenderer->meshesUI.push_back(m);
	return GO;
}

