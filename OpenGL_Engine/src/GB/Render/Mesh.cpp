#include "gbpch.h"
#include "Mesh.h"
#include "imgui.h"

namespace GB
{
	Mesh::Mesh()
	{
		vertices = std::vector<vector3>();

	}
	std::vector<vector3> Mesh::GetEqualsVector(const std::vector<vector3> mesh1, const std::vector<vector3> mesh2)
	{
		std::vector<vector3> temp;
		int count = 0;

		for ( size_t i = 0; i < mesh1.size(); i++)
		{
			for (size_t j = 0; j < mesh2.size(); j++)
			{
				if (mesh1[i] == mesh2[j])
				{
					temp.push_back(mesh1[i]);
				}
				count++;
			}
		}
		GB_CORE_INFO("There is a total number of {0} count vector from getdifferences");
		return temp;
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