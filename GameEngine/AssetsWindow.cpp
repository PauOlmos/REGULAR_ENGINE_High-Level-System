#include "Application.h"
#include "AssetsWindow.h"
#include "HeaderMenu.h"
#include "PhysFS/include/physfs.h"

AssetsWindows::AssetsWindows(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	PHYSFS_init(nullptr);
	PHYSFS_mount(".", nullptr, 1);
}

AssetsWindows::~AssetsWindows()
{
	PHYSFS_deinit();
}

bool AssetsWindows::Init()
{
	PHYSFS_addToSearchPath("Assets", 1);

	return true;
}

bool AssetsWindows::Start()
{
	bool ret = true;

	return ret;
}

bool AssetsWindows::CleanUp()
{

	return true;
}

update_status AssetsWindows::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

update_status AssetsWindows::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (HMenu::openAssets)
	{
		HMenu::ThemeStyleWind();
		HMenu::ThemeStylePopUp();

		ImGui::Begin("Assets", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

		if (ImGui::BeginMenuBar())
		{
			PrintAssetsMenu((char*)pathName.c_str());
			ImGui::EndMenuBar();
		}

		PrintAssets((char*)pathName.c_str());

		ImGui::End();

		ImGui::PopStyleColor(4);
	}

	return ret;
}

update_status AssetsWindows::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
}

void AssetsWindows::PrintAssets(char* path)
{
	//LOG("%s", PHYSFS_getBaseDir());
	//LOG("%s", PHYSFS_getUserDir());

	//Show the files in this path
	char** rc = PHYSFS_enumerateFiles(path);
	char** i;
	ImGui::Separator();

	for (i = rc; *i != NULL; i++)
	{
		string pName = *i;

		if (pName.find(".") == -1)
		{
			if (ImGui::Button(*i, ImVec2(125, 30)))
			{
				pathName.append("/");
				pathName.append(*i);
				PrintAssets((char*)pathName.c_str());
			}
			ImGui::Separator();
		}
	}

	for (i = rc; *i != NULL; i++)
	{
		string pName = *i;

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
		bool y;

		if (pName.find(".") != -1)
		{
			y = ImGui::TreeNodeEx((void*)(intptr_t)i, treeNodeFlags, pName.c_str());
			ImGui::Separator();
		}
		else
			y = false;


		if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
		{

		}



		if (y)
		{
			ImGui::TreePop();
		}
	}

	/*ImGui::Separator();
	if (ImGui::Button("Create"))
	{
		PHYSFS_mkdir("Biel/");
	}*/
		//LOG(" * We've got [%s].\n", *i);

	PHYSFS_freeList(rc);
}

void AssetsWindows::PrintAssetsMenu(char* path)
{
	string pa = path;
	string pat = path;		//		Assets/street
	
	while (pa.size() != 0)
	{
		int pos = pa.find_first_of("/");

		if (pos == -1) {
			ImGui::Text(pa.c_str());
			break;
		}

		if (ImGui::Button(pa.substr(0, pos).c_str()))
		{
			// end = folder inside (ex: street)
			string end = pa.substr(0, pa.find_first_of("/"));
			// pathName = full path (ex: Assets/street)
			pathName = pat.substr(0, pat.find(end) + end.size());
			break;
		}

		ImGui::Text("->");

		pa = pa.substr(pos + 1);
	}

}