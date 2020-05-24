#include "gbpch.h"
#include "GB/Render/RenderCommand.h"
#include "RendererMenu.h"
#include "imgui.h"
namespace GB
{
	void RenderTab::Update()
	{
		static bool alpha = true;
		static bool depth = true;
		static float colors[3] = { 0.5f,0.2f,0.3f };
		ImGui::Text("Render Actions");

		if (ImGui::Button("Toggle alpha mode"))
		{
			alpha = !alpha;
			RenderCommand::AlphaMode(alpha);
		}
		if (ImGui::Button("Toggle Depht Test"))
		{
			depth = !depth;
			RenderCommand::DephtTest(depth);
		}
		
		if (ImGui::ColorPicker3("Background Color", colors))
		{
			RenderCommand::SetClearColor(glm::vec4(colors[0], colors[1], colors[2], 1.0f));
		}


		ImGui::Text("Create");

		if (ImGui::Button("Create plane"))
		{

		}
		if (ImGui::Button("Create cube"))
		{

		}
	}

}