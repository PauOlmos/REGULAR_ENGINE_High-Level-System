#include "GameWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"
#include "ComponentCamera.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"
#include "Transform.h"
#include "SceneWindow.h"
#include "ModuleUI.h"

ImVec2 GameWindows::sizeWindScn = { 0,0 };

void GameWindows::PrintCamera(Application* app)
{
	//Begin scene & get size
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Game", 0, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNavFocus);
	sizeWindScn = ImGui::GetContentRegionAvail();

	//Get proportion, and match with 16:9
	ImVec2 newWinSize = sizeWindScn;
	newWinSize.x = (newWinSize.y / 9.0f) * 16.0f;

	//Get uv's offset proportionate to image
	float uvOffset = (sizeWindScn.x - newWinSize.x) / 2.0f;
	uvOffset /= newWinSize.x;
	//Print image (window size), modify UV's to match 
	if (app->renderer3D->GetMainCamera() != nullptr)
		ImGui::Image((ImTextureID)app->renderer3D->GetMainCamera()->cameraBuffer, sizeWindScn, ImVec2(-uvOffset, 1), ImVec2(1 + uvOffset, 0));

	std::vector<GameObject*> PickedGOs;

	int mouse_x, mouse_y;

	Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

	if ((mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) && app->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT && ImGui::IsWindowHovered())
	{
		//Close GO options menu
		app->hierarchy->openGOOptions = false;

		GameObject* klk = nullptr;

		ImVec2 mousePos = ImGui::GetMousePos();

		ImVec2 norm = SceneWindows::NormMousePos(ImGui::GetWindowPos().x,
			ImGui::GetWindowPos().y + ImGui::GetFrameHeight(),
			ImGui::GetWindowSize().x,
			ImGui::GetWindowSize().y - ImGui::GetFrameHeight(), mousePos);

		LineSegment picking = app->camera->cam->frustum.UnProjectLineSegment(norm.x, norm.y);

		app->meshRenderer->debugRaycastA = picking.a;
		app->meshRenderer->debugRaycastB = picking.b;

		app->UI->whichMesh = MPUI(picking, app->meshRenderer->meshesUI);

		if (app->UI->whichMesh >= 0) {
			klk = app->meshRenderer->meshesUI[app->UI->whichMesh]->myGameObject;
			if (klk->type == GOtype::UI_CHECKBOX && app->UI->count == 0) {
				ComponentTexture* ct = klk->GetComponent<ComponentTexture>();
				klk->activeState = !klk->activeState;
				app->UI->count = 1;
				if (klk->activeState == true) {
					ct->SetTexture("Assets/green.png");
				}
				else {
					ct->SetTexture("Assets/red.png");
				}
				if (klk->subname == "VsyncButton") {
					SDL_GL_SetSwapInterval(klk->activeState);
					LOGT(LogsType::SYSTEMLOG, "Vsync active: %d", klk->activeState);
				}
			}
			if (klk->type == GOtype::UI_BUTTON && app->UI->released == false) {
				ComponentTexture* ct = klk->GetComponent<ComponentTexture>();
				ct->SetTexture("Assets/yellow.png");
				//DOSMTH
				if (klk->subname == "ClearFirstStage") {
					ButtonAction();
				}
				app->UI->released = true;
			}
			app->UI->movingAny = true;
		}
		else app->UI->movingAny = false;
		if (klk != nullptr) {
			if (klk->Dragable && !app->IsRunning()) {
				if (klk != nullptr && app->UI->mouse_x_aux != 0) {
					float x = klk->transform->getPosition().x - (mouse_x - app->UI->mouse_x_aux) / 500.0f;
					float y = klk->transform->getPosition().y - (mouse_y - app->UI->mouse_y_aux) / 500.0f;
					float z = klk->transform->getPosition().z;
					app->meshRenderer->meshesUI[app->UI->whichMesh]->myGameObject->transform->setPosition({ x,y,z });
				}
			}
		}

		SDL_GetMouseState(&app->UI->mouse_x_aux, &app->UI->mouse_y_aux);

		PickedGOs.push_back(klk);

		app->hierarchy->SetGameObjectSelected(klk);
		if (PickedGOs.size() == 0) app->hierarchy->SetGameObjectSelected(nullptr);
		PickedGOs.clear();
	}
	else {
		app->UI->count = 0;
		app->UI->mouse_x_aux = 0;
		app->UI->mouse_y_aux = 0;
	}
	if (app->UI->whichMesh != -1 && app->meshRenderer->meshesUI.size()>0){

		if (!(mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) && app->meshRenderer->meshesUI[app->UI->whichMesh]->myGameObject->type == GOtype::UI_BUTTON) {
			app->meshRenderer->meshesUI[app->UI->whichMesh]->myGameObject->GetComponent<ComponentTexture>()->ResetTexture();
			app->UI->released = false;
		}
}

	ImGui::End();
	ImGui::PopStyleVar();
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameWindows::ButtonAction() {
	Application::GetInstance()->dummy->secondStageStarted = true;
}

int GameWindows::MPUI(LineSegment picking, vector<Mesh*> meshList){

	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (picking.a.x <meshList[i]->myGameObject->transform->getScale().x * 0.07 + meshList[i]->myGameObject->transform->getPosition().x * 2 * 0.07
			&& picking.a.x > meshList[i]->myGameObject->transform->getScale().x * -0.07 - meshList[i]->myGameObject->transform->getPosition().x * 2 * -0.07
			&& picking.a.y < meshList[i]->myGameObject->transform->getScale().y * 0.05 + meshList[i]->myGameObject->transform->getPosition().y * 2 * 0.06
			&& picking.a.y > meshList[i]->myGameObject->transform->getScale().y * -0.05 - meshList[i]->myGameObject->transform->getPosition().y * 2 * -0.055) {
			return i;
		}
	}
	return -1;
}