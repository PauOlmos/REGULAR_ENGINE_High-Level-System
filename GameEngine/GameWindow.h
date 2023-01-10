#pragma once
#include "Application.h"

using namespace std;

class GameWindows
{
public:
	static void PrintCamera(Application* app);

	static GameObject* MPUI(LineSegment picking, vector<Mesh*> meshList);

private:

	static ImVec2 sizeWindScn;
};