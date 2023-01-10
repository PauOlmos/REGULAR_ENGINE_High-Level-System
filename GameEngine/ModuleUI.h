#pragma once

#include "Module.h"
#include "GameObject.h"

enum class UIType {
	NORMAL,BUTTON,SLIDER,TEXT_INPUT,CHECKBOX
};

class ModuleUI : public Module
{
public:
	CameraComponent* UICam;

	ModuleUI(Application* app, bool start_enabled = true);

	// Destructor
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool movingAny = false;

	int whichMesh = NULL;

	int count = 0;

	int wtf = 0;

	int mouse_x_aux = 0, mouse_y_aux = 0;

	static GameObject* CreateUI(UIType GOtype);
	static GameObject* CreateUICrosshair(UIType GOtype);

};
