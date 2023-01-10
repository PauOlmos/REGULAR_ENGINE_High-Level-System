#include "GameWindow.h"
#include "imgui.h"
#include "HeaderMenu.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "Transform.h"
#include "SceneWindow.h"

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
	if(app->renderer3D->GetMainCamera() != nullptr)
		ImGui::Image((ImTextureID)app->renderer3D->GetMainCamera()->cameraBuffer, sizeWindScn, ImVec2(-uvOffset, 1), ImVec2(1 + uvOffset, 0));
	if (ImGui::IsMouseClicked(0) && app->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT && ImGui::IsWindowHovered())
	{
		//Close GO options menu
		app->hierarchy->openGOOptions = false;

		std::vector<GameObject*> PickedGOs;
		GameObject* klk = nullptr;

		ImVec2 mousePos = ImGui::GetMousePos();

		ImVec2 norm = SceneWindows::NormMousePos(ImGui::GetWindowPos().x,
			ImGui::GetWindowPos().y + ImGui::GetFrameHeight(),
			ImGui::GetWindowSize().x,
			ImGui::GetWindowSize().y - ImGui::GetFrameHeight(), mousePos);

		LineSegment picking = app->camera->cam->frustum.UnProjectLineSegment(norm.x, norm.y);

		app->meshRenderer->debugRaycastA = picking.a;
		app->meshRenderer->debugRaycastB = picking.b;

		klk = MPUI(picking, app->meshRenderer->meshesUI);

		PickedGOs.push_back(klk);

		app->hierarchy->SetGameObjectSelected(klk);


		if (PickedGOs.size() == 0) app->hierarchy->SetGameObjectSelected(nullptr);
		PickedGOs.clear();
	}
	ImGui::End();
	ImGui::PopStyleVar();
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GameObject* GameWindows::MPUI(LineSegment picking, vector<Mesh*> meshList) {

	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (picking.a.x <meshList[i]->myGameObject->transform->getScale().x * 0.07 + meshList[i]->myGameObject->transform->getPosition().x * 2 * 0.07
			&& picking.a.x > meshList[i]->myGameObject->transform->getScale().x * -0.07 - meshList[i]->myGameObject->transform->getPosition().x * 2 * -0.07
			&& picking.a.y < meshList[i]->myGameObject->transform->getScale().y * 0.05 + meshList[i]->myGameObject->transform->getPosition().y * 2 * 0.06
			&& picking.a.y > meshList[i]->myGameObject->transform->getScale().y * -0.05 - meshList[i]->myGameObject->transform->getPosition().y * 2 * -0.055) {
			return meshList[i]->myGameObject;
		}
	}
	return nullptr;
}