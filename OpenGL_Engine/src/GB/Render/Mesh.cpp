#include "gbpch.h"
#include "Mesh.h"
#include "imgui.h"

namespace GB
{
	Mesh::Mesh()
	{
		vertices = std::vector<vector3>();

	}
	void Mesh::WindowProperties()
	{

		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::Text("Vertices count [%d]", this->vertices.size());
			ImGui::Text("Indices vertices count [%d]", this->indicesVertices.size());
			ImGui::Text("UV count [%d]", this->uv.size());
			ImGui::Text("Normals count [%d]", this->normals.size());

			if (ImGui::CollapsingHeader("Vertices"))
				for (size_t i = 0; i < this->vertices.size(); i++)
				{
					ImGui::Text("vertices [%d]: %f,%f,%f", i, vertices[i].x, vertices[i].y, vertices[i].z);
				}
			if (ImGui::CollapsingHeader("UV"))
				for (size_t i = 0; i < this->uv.size(); i++)
				{
					ImGui::Text("UV [%d]: %f,%f", i, uv[i].x, uv[i].y);
				}
			if(ImGui::CollapsingHeader("Normals"))
				for (size_t i = 0; i < this->normals.size(); i++)
				{
					ImGui::Text("Normals [%d]: %f,%f,%f", i, normals[i].x, normals[i].y,normals[i].z);
				}
			if (ImGui::CollapsingHeader("Indices"))
			{
				for (size_t i = 0; i < this->indicesVertices.size(); i++)
				{
					ImGui::Text("Indice [%d]: %f", i, this->indicesVertices[i]);
				}
			}
			ImGui::Spacing();
		}
	}

}