#include "gbpch.h"
#include "MenuLayer.h"
#include "imgui.h"
#include "GB/ImportTools/IO.h"

namespace GB
{
	//this is to test the import tools and save levels
	struct DATA
	{
		float position;
		int value;
		uint32_t ID;

		std::string name;
	};
	EditorMenu::EditorMenu()
	{
		m_MenuName = "Test";
	}
	void EditorMenu::ImguiRender()
	{
		static bool m_state = true;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					DATA data = { 20,1,2,"Eva" };

					IO::WriteFile(data, "foo.gb");
				}
				if (ImGui::MenuItem("Open"))
				{
					DATA data = IO::ReadFile<DATA>("foo.gb");
					GB_CORE_TRACE("DATA: {0},{1},{2},{3}", data.ID, data.position, data.name.c_str(),data.value);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();	
		}


	}

	void EditorMenu::RemoveAction()
	{

	}

	void EditorMenu::AddAction(const std::string& name)
	{
	}

}
