#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Logs.h"
#include "HeaderMenu.h"
#include "Config.h"
#include "AssetsWindow.h"
#include "Inspector.h"
#include "Primitives.h"
#include "Transform.h"
#include "ComponentCamera.h"

#include "ComponentMesh.h"

ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	cameraController = nullptr;
}

ModuleDummy::~ModuleDummy()
{

}

bool ModuleDummy::Start()
{
	LOG("Testing");
	bool ret = true;

	GameObject* go = App->meshRenderer->LoadFile("Assets/street/scene.DAE");
	go->transform->setRotation(float3(0, 0, -90));

	cameraController = Primitives::CreatePrimitive(Shapes::CAMERA);
	cameraController->transform->setPosition(float3(0, 2, -10));
	cameraController->transform->setRotation(float3(0, 0, 0));

	angle = 0;

	return ret;
}

bool ModuleDummy::CleanUp()
{
	cameraController = nullptr;

	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if(cameraController->isChildFrom(App->hierarchy->rootHierarchy))
	if (App->IsRunning()) {
		if (!finalStage) {
			FirstStage();
			if (secondStageStarted) SecondStage();
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && VsyncStageActive == false) {
				VsyncStage();
			}
			if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && VsyncStageActive == true) {
				VsyncStageDisable();
			}
			if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
				VsyncStageActive = !VsyncStageActive;
			}
			

		}
	}

	return ret;
}

void ModuleDummy::FirstStage() {
	if (justOnce == false) {
		App->UI->CreateUI(UIType::BUTTON);
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->subname = "ClearFirstStage";
		App->UI->CreateUI(UIType::NORMAL);
		justOnce = true;
	}
}

void ModuleDummy::SecondStage() {
	firstMovY = App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->getPosition().y - 0.05f;
	App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->setPosition({ App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->getPosition().x,firstMovY,App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->getPosition().z });		secondMovY = App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 2]->myGameObject->transform->getPosition().y - 0.05f;		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 2]->myGameObject->transform->setPosition({ App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 2]->myGameObject->transform->getPosition().x,secondMovY,App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 2]->myGameObject->transform->getPosition().z });
	if (secondMovY <= -2) {
		secondStageStarted = false;
		App->UI->CreateUICrosshair(UIType::NORMAL);
		finalStage = true;
	}
}

void ModuleDummy::VsyncStage()
{
	if (App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 2]->myGameObject->subname == "VsyncButton") {
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 3]->myGameObject->transform->setPosition({ 1000,1000,1 });
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->setPosition({ 0,0,1 });
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 2]->myGameObject->transform->setPosition({ 0,0,1 });
	}
	else {
		App->UI->CreateUI(UIType::CHECKBOX);
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->subname = "VsyncButton";
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->setScale({0.2,0.2,1});
		App->UI->CreateUI(UIType::NORMAL);
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->setScale({ 1,1,1 });
		App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 3]->myGameObject->transform->setPosition({ 1000,1000,1000 });
		//App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 3]->myGameObject->transform->setPosition({ 0,0,1 });
	}
}

void ModuleDummy::VsyncStageDisable()
{
	App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 1]->myGameObject->transform->setPosition({1000,1000,1});
	App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 2]->myGameObject->transform->setPosition({1000,1000,1});
	App->meshRenderer->meshesUI[App->meshRenderer->meshesUI.size() - 3]->myGameObject->transform->setPosition({0,0,1});
}

update_status ModuleDummy::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	HMenu::ThemeStyleWind();
	HMenu::ThemeStyleMenuBar();
	HMenu::ThemeStylePopUp();
	
	//ImGui::ShowDemoWindow();
	//Print Multiple Windows
	
	//if (HMenu::openAssets)
	//AssetsWindows::PrintAssets();

	if(HMenu::openConsole)
		Logs::PrintDebug();

	if(HMenu::openConig)
		ConfigWindow::PrintConfig(App, dt);

	if (HMenu::openInspector)
		InspectorMenu::PrintInspector();
	
	ImGui::PopStyleColor(6);

	//close the engine
	if (HMenu::quit)
	{
		ret = UPDATE_STOP;
	}

	return ret;
}