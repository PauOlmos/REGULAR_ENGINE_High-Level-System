#pragma once

#include "Module.h"
#include "GameObject.h"
#include "ComponentUICamera.h"

enum class UIType {
	NORMAL,BUTTON,SLIDER,TEXT_INPUT
};

class ModuleUI : public Module
{
public:
	UICameraComponent* UIcc = new UICameraComponent();
	UICameraComponent* UICam;

	ModuleUI(Application* app, bool start_enabled = true);

	// Destructor
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	static GameObject* CreateUI(UIType GOtype);

};
