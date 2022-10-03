#include "Globals.h"
#include "Application.h"
#include "ModuleDummy.h"
#include "ModuleRenderer3D.h"
#include "glew.h"
#include "Primitive.h"


ModuleDummy::ModuleDummy(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleDummy::~ModuleDummy()
{

}

bool ModuleDummy::Start()
{
	LOG("Testing");
	bool ret = true;

	App->camera->Position = vec3(1.f, 1.f, 0.0f);
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

bool ModuleDummy::CleanUp()
{
	LOG("Cleaning test");

	return true;
}

update_status ModuleDummy::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleDummy::Update(float dt)
{
	static int counter = 0;

	ImGui::Begin("HE", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::CollapsingHeader("Button"))
	{
		if (ImGui::Button("Exit"))
		{
			return UPDATE_STOP;
		}
		ImGui::SameLine();
		if (ImGui::ColorButton("ColBut", {1,0,0,1}))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::SmallButton("Small"))
		{
			counter++;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Radio", IsWireframe)) //the true or false its to light up the button
		{
			counter++;
			IsWireframe = !IsWireframe;
		}

		ImGui::Text("counter = %d", counter);
	}

	if (ImGui::CollapsingHeader("Color"))
	{
		ImGui::ColorEdit4("Color Edit", colorEdit);
		//ImGUi::
		ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f,0.5f);
	}

	if (ImGui::CollapsingHeader("Info Guide"))
		ImGui::ShowUserGuide();

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Text"))
		{ 
			if (ImGui::BeginMenu("SubText"))
			{
					ImGui::Text("Yes bby\n shit happens \"My Love\"");
					ImGui::SameLine();
					ImGui::TextColored({ 0.9f,0.0f,0.0f,0.9f }, "NOPPP");
					ImGui::BulletText("YASSS\n \"The Y\" for the frineds");
					ImGui::Separator();
					ImGui::TextWrapped("YEY");
					ImGui::Separator();
					ImGui::TextUnformatted("YEY");
					ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Info"))
		{
			if (ImGui::Button("Popup"))
			{
				ImGui::OpenPopup("another popup");
			}
			if (ImGui::BeginPopup("another popup"))
			{
				//ImGui::Text("");

				ImGui::Begin("Settings");
				ImGui::Text("Yes bby\n shit happens \"My Love\"");
				ImGui::End();
				ImGui::EndPopup();
			}

			//ImGui::
			/*if (ImGui::Button("Open"))
			{
				ImGui::Begin("Settings");
				ImGui::Text("Yes bby\n shit happens \"My Love\"");
				ImGui::End();
			}*/

			//infoWind = !infoWind;
			ImGui::EndMenu();

		}

		if (infoWind)
		{

		}

		ImGui::BeginPopup;

		ImGui::EndMenuBar();
	}

	if (ImGui::IsKeyReleased(ImGuiKey_Tab))
	{
		counter++;
	}
	

	ImGui::End();


	ImGui::Begin("Console", 0, ImGuiInputTextFlags_CallbackResize);
	

	ImGui::End();

	return UPDATE_CONTINUE;

}

update_status ModuleDummy::PostUpdate(float dt)
{

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	Cube c(1, 1, 1);
	c.Render();


	if(IsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//CAN RENDER
	glBegin(GL_TRIANGLES);

	glVertex3f(0.f, 0.5f, 0.f);
	glVertex3f(0.f, 1.5f, 0.f);
	glVertex3f(0.f, 0.5f, 1.f);


	glEnd();
	//

	/*
	glBegin(GL_TRIANGLES);

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 10.f, 0.f);
	glEnd();

	glLineWidth(1.0f);*/
	
	PrintDebug(par);
	return UPDATE_CONTINUE;
}

void ModuleDummy::PrintDebug(char* a)
{
	char b = *a;
	char c[10] = { "hye" };
	char logsConsol[32][32] = {  };

	ImGui::Begin("Console", 0, ImGuiInputTextFlags_CallbackResize);

	ImGui::InputText("text", c, IM_ARRAYSIZE(c));
	
	char printConsol[IM_ARRAYSIZE(logsConsol)] = {};
	//*printConsol = *logsConsol;

	logsConsol[0][0] = {'a'};
	logsConsol[0][1] = {'b'};
	logsConsol[1][0] = {'c'};
	logsConsol[1][1] = {'d'};

	/*for (size_t i = 0; i < IM_ARRAYSIZE(logsConsol); i++)
	{
		for (size_t j = 0; j < IM_ARRAYSIZE(logsConsol); j++)
		{
			ImGui::Text(&logsConsol[j][i]);
		}
	}*/

	for (size_t i = 0; i < IM_ARRAYSIZE(logsConsol); i++)
	{
		for (size_t j = 0; j < IM_ARRAYSIZE(logsConsol); j++)
		{
			ImGui::Text(&logsConsol[j][i]);
		}
	}


	ImGui::End();

}