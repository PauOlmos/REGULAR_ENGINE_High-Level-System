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

ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	house = nullptr;
	cube = nullptr;
	sphere = nullptr;
	cameraController = nullptr;
}

ModuleDummy::~ModuleDummy()
{

}

bool ModuleDummy::Start()
{
	LOG("Testing");
	bool ret = true;

	house = App->meshRenderer->LoadFile("Assets/BakerHouse.fbx");

	cube = Primitives::CreatePrimitive(Shapes::CUBE);
	cube->transform->setPosition(float3(-3, 0, 0));

	sphere = Primitives::CreatePrimitive(Shapes::SPHERE);
	sphere->transform->setPosition(float3(3, 0, 0));

	cameraController = Primitives::CreatePrimitive(Shapes::CAMERA);
	cameraController->transform->setPosition(float3(0, 2, -10));
	cameraController->transform->setRotation(float3(0, 0, 0));

	angle = 0;

	return ret;
}

bool ModuleDummy::CleanUp()
{	
	delete house;
	delete cube;
	delete sphere;
	delete cameraController;

	house = nullptr;
	cube = nullptr;
	sphere = nullptr;
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

	if (App->GetIsRunning()) {
		angle += 30 * App->GetDTG();

		cameraController->transform->setPosition(float3(cos(angle * DEGTORAD) * -10, 2, sin(angle * DEGTORAD) * -10));
		cameraController->transform->setRotation(float3(0, angle - 90, 0));

		if (angle > 360.0f) angle -= 360.0f;
	}

	return ret;
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