#include "gbpch.h"
#include "Render2D.h"
#include "imgui.h"

void GB::Render2D::OnUpdate(float DeltaTime)
{
}

void GB::Render2D::ImguiRender()
{
	ImGui::Text("Render2D There is no GUI in this component");
}

int GB::Render2D::ID()
{
	return 0;
}

void GB::MeshRenderer::OnUpdate(float DeltaTime)
{
	GB_CORE_INFO("Updating meshrenderer");
}

void GB::MeshRenderer::ImguiRender()
{
	//throw std::logic_error("The method or operation is not implemented.");
}
