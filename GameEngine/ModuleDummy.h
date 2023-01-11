#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"

#include "MathGeoLib.h"

#include "Logs.h"

#include "GameObject.h"

#include <string>
#include <vector>

class ModuleDummy : public Module
{
public:

	ModuleDummy(Application* app, bool start_enabled = true);
	~ModuleDummy();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	void FirstStage();
	void SecondStage();
	void VsyncStage();
	void VsyncStageDisable();
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool justOnce = false;
	bool secondStageStarted = false;
	bool finalStage = false;
	bool VsyncStageActive = false;
	float firstMovY = 0;
	float secondMovY = 0;
	//GameObject* firstMenuItem, secondMenuItem;

private:
	GameObject* cameraController;
	float angle;
};