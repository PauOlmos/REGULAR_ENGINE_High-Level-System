#pragma once
#include "Component.h"
#include "MathGeoLib.h"

struct Mesh;

class UICameraComponent : public Component
{
public:
	UICameraComponent();
	~UICameraComponent();

	void SetAspectRatio(float aspectRatio = 1.7);

	float* GetViewMatrix();
	float* GetProjetionMatrix();

	bool IsInsideFrustum(Mesh* mesh);

	void PrintUI();

	Frustum frustum;

	int typeCameraSelected = 0;

	int cameraFOV = 60;
	float farDistance = 500.0f;
	float nearDistance = 0.1f;

	unsigned int UIcameraBuffer;
private:
	float4x4 UIviewMatrix;
	float4x4 UIprojectionMatrix;
};