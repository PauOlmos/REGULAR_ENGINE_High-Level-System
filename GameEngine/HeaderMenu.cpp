#include "HeaderMenu.h"
#include "imgui.h"
#include "SDL.h"
#include "Primitives.h"
#include "Application.h"

bool HMenu::quit = false;
bool HMenu::openInspector = true;
bool HMenu::openConsole = true;
bool HMenu::openConig = true; 
bool HMenu::openHierarchy = true;
bool HMenu::openAssets = true;
bool HMenu::styleSelectD = false;
bool HMenu::styleSelectL = false;
bool HMenu::styleSelectSD = true;
bool HMenu::styleSelectP = false;
bool HMenu::isWireframe = false;

bool HMenu::popUpAbout = false;

int HMenu::colorStyle = 3;

float HMenu::colorWind[4] = { 0.4f, 0.7f, 0.0f, 1.0f };
float HMenu::colorText[4] = { 0.9f, 0.0f, 1.0f, 1.0f };

void HMenu::PrintMenu(Application* app)
{
	ThemeStylePopUp();
	ThemeStyleMenuBar();

	if (ImGui::BeginMainMenuBar())
	{	
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("  About  "))
			{
				popUpAbout = !popUpAbout;
			}

			if (ImGui::MenuItem("  Git Hub  "))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("GitHub", ImVec2(60, 20)))
				ShellExecute(0, 0, "https://github.com/bielrabasa/TheSeed_GameEngine", 0, 0, SW_SHOW);

			if (ImGui::MenuItem("  Exit  "))	//Try with 2 typs, MenuItem & Button
			//if (ImGui::Button("Exit", ImVec2(60, 20)))
				quit = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Basic Shapes"))
		{
			if (ImGui::MenuItem(" Empty Object  ")) {
				Primitives::CreatePrimitive(Shapes::EMPTY);
			}

			if (ImGui::MenuItem(" Plane  "))
			{
				Primitives::CreatePrimitive(Shapes::PLANE);
			}

			if (ImGui::MenuItem(" Cube  "))
			{
				Primitives::CreatePrimitive(Shapes::CUBE);
			}

			if (ImGui::MenuItem(" Sphere  "))
			{
				Primitives::CreatePrimitive(Shapes::SPHERE);
			}


			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			
			if (ImGui::RadioButton(" Inspector  ", openInspector))
			{
				openInspector = !openInspector;
			}

			if (ImGui::RadioButton(" Hierarchy  ", openHierarchy))
			{
				openHierarchy = !openHierarchy;
			}

			if (ImGui::RadioButton(" Console  ", openConsole))
			{
				openConsole = !openConsole;
			}

			if (ImGui::RadioButton(" Config  ", openConig))
			{
				openConig = !openConig;
			}
			
			if (ImGui::RadioButton(" Assets  ", openAssets))
			{
				openAssets = !openAssets;
			}

			ImGui::Separator();

			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem(" Light  ", NULL, &styleSelectL))
				{
					colorStyle = 1;
					styleSelectL = true;
					styleSelectD = false;
					styleSelectSD = false;
					styleSelectP = false;
				}
				if (ImGui::MenuItem(" Soft Dark  ", NULL, &styleSelectSD))
				{
					colorStyle = 3;
					styleSelectL = false;
					styleSelectD = false;
					styleSelectSD = true;
					styleSelectP = false;
				}
				if (ImGui::MenuItem(" Dark  ", NULL, &styleSelectD))
				{
					colorStyle = 2;
					styleSelectL = false;
					styleSelectD = true;
					styleSelectSD = false;
					styleSelectP = false;
				}

				if (ImGui::BeginMenu(" Personified"))
				{
					ImGui::ColorEdit4("Windows Color", colorWind);
					ImGui::ColorEdit4("Text Color", colorText);

					if (ImGui::MenuItem(" Apply  ", NULL, &styleSelectP))
					{
						colorStyle = 4;
						styleSelectL = false;
						styleSelectD = false;
						styleSelectSD = false;
						styleSelectP = true;
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Render"))
		{
			if (ImGui::RadioButton(" Wireframe  ", isWireframe))
			{
				isWireframe = !isWireframe;
			}
			ImGui::EndMenu();
		}
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);
		ImGui::PopStyleColor(1);

		ImGui::EndMainMenuBar();
	}

	if (popUpAbout)
	{
		if(ImGui::Begin("About", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
		{ 
			ImGui::BulletText("The Seed Engine is a \ngame engine developed \nby Biel Rabasa and \nRoger Salas");
			ImGui::BulletText("To import files and \ntextures, drag and drop \nthe files");
			ImGui::BulletText("To move the camera visit \nour GitHub and check \nthe controls");

			ImGui::Text("");

			ImGui::BulletText("You can finde more in \nour GitHub");

			ImGui::End();
		}
	}

	ImGui::SameLine(ImGui::GetWindowWidth() / 2 - 37);
	{
		if (ImGui::Button(">", ImVec2(25, 25)))
		{
			LOG("Play");
			//app->SetDTG();
		}

		ImGui::SameLine();

		if (ImGui::Button("||", ImVec2(25, 25)))
		{
			LOG("Pause");
			//app->PauseDGT();
		}

		ImGui::SameLine();

		if (ImGui::Button("[]", ImVec2(25, 25)))
		{
			LOG("Stop");
			//app->StopDTG();
		}
	}
}

void HMenu::ThemeStylePopUp()
{
	if (colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.2f, 0.2f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 4)
	{
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(colorWind[0], colorWind[1], colorWind[2], colorWind[3]));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(colorText[0], colorText[1], colorText[2], colorText[3]));
	}
}

void HMenu::ThemeStyleMenuBar()
{
	if (colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0, 0, 0, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(1, 1, 1, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.2f, 0.2f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 4)
	{
		ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(colorWind[0], colorWind[1], colorWind[2], colorWind[3]));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(colorText[0], colorText[1], colorText[2], colorText[3]));
	}
}

void HMenu::ThemeStyleWind()
{
	if (HMenu::colorStyle == 2)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 1)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.9, 0.9, 0.9, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1.f));
	}
	else if (HMenu::colorStyle == 3)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));
	}
	else if (HMenu::colorStyle == 4)
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(colorWind[0], colorWind[1], colorWind[2], colorWind[3]));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(colorText[0], colorText[1], colorText[2], colorText[3]));
	}
}