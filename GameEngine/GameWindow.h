#pragma once
#include "Application.h"

using namespace std;

class GameWindows
{
public:
	static void PrintCamera(Application* app);

	static void ButtonAction();

	static int MPUI(LineSegment picking, vector<Mesh*> meshList);

private:

	static ImVec2 sizeWindScn;
};