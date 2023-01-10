#include "Application.h"
#include "ComponentUICamera.h"
#include "GameObject.h"
#include "Transform.h"
#include "imgui.h"
#include "ModuleMesh.h"
#include "ModuleMesh.h"

class ComponentMesh;

UICameraComponent::UICameraComponent()
{

	//Component
	type = ComponentType::UICAMERA;
	containerParent = nullptr;

	//Frustum
	frustum.type = OrthographicFrustum;
	frustum.nearPlaneDistance = nearDistance;
	frustum.farPlaneDistance = farDistance; //inspector
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.verticalFov = cameraFOV * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f); // 16:9 ~= 1,77777...
	frustum.pos = float3(0, 0, 0);
}

UICameraComponent::~UICameraComponent()
{

}

void UICameraComponent::SetAspectRatio(float aspectRatio)
{
	frustum.verticalFov = cameraFOV * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * aspectRatio);
}

float* UICameraComponent::GetViewMatrix()
{

	UIviewMatrix = frustum.ViewMatrix();
	UIviewMatrix.Transpose();
	return UIviewMatrix.ptr();
}

float* UICameraComponent::GetProjetionMatrix()
{
	UIprojectionMatrix = frustum.ProjectionMatrix();
	UIprojectionMatrix.Transpose();
	return UIprojectionMatrix.ptr();
}

bool UICameraComponent::IsInsideFrustum(Mesh* mesh)
{
	/*float3 boxPoints[8];
	Plane frustumPlanes[6];

	mesh->Global_AABB_box.GetCornerPoints(boxPoints);
	frustum.GetPlanes(frustumPlanes);

	//Check all frustum planes
	for (size_t i = 0; i < 6; i++)
	{
		int p = 0;

		//Check all box points to each frustum plane
		for (size_t j = 0; j < 8; j++)
		{
			if (frustumPlanes[i].IsOnPositiveSide(boxPoints[j]))
				p++;
		}

		//Check if all points are outside
		if (p == 8) {
			//All points outside one of the planes -> outside frustum
			return false;
		}
	}

	//AABB box is at least partially inside frustum
	return true;*/
	return true;
}

void UICameraComponent::PrintUI()
{
	Application::GetInstance()->meshRenderer->RenderUI();
}

