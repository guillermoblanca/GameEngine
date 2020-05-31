#include "gbpch.h"
#include "Mesh.h"
#include "imgui.h"

namespace GB
{
	Mesh::Mesh()
	{
		vertices = std::vector<vector3>();
		indicesVertices = std::vector<unsigned int>();

		uv = std::vector<vector2>();
		indicesUV = std::vector<unsigned int>();

		normals = std::vector<vector3>();
		indicesNormals = std::vector<unsigned int>();
		debugInfo = std::vector<std::string>();
		name = "BaseMesh";
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
			if (ImGui::CollapsingHeader("Normals"))
				for (size_t i = 0; i < this->normals.size(); i++)
				{
					ImGui::Text("Normals [%d]: %f,%f,%f", i, normals[i].x, normals[i].y, normals[i].z);
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

	Mesh* Mesh::Create(const char* path)
	{
		Mesh* mesh = new Mesh();
		mesh = MeshReader::ReadMeshFromFile(path);
		

		return mesh;
	}


	Mesh* MeshReader::ReadMeshFromFile(const char* path)
	{

		std::vector<vector3> temp_Vertices;
		std::vector<vector2> temp_UV;
		std::vector<vector3> temp_Normals;
		std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
		Mesh* mesh = new Mesh();

		FILE* file = fopen(path, "r");

		if (file == NULL)
		{
			GB_CORE_ERROR("ERROR READING FILE OBJ: {0}", path);
			return nullptr;
		}

		bool active = true;
		char lineHeader[128]; //sho

		while (active)
		{
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)break;

			if (strcmp(lineHeader, "v") == 0)
			{
				vector3 vertex;
				fscanf(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
				temp_Vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				vector2 uv;
				fscanf(file, "%f %f \n", &uv.x, &uv.y);
				temp_UV.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_Normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				uint32_t vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9)
				{
					GB_CORE_ERROR("File can't be read! try other configurations matches expected: 9: {0}", matches);

					return nullptr;
				}
				vertexIndices.push_back(vertexIndex[0]-1);
				vertexIndices.push_back(vertexIndex[1]-1);
				vertexIndices.push_back(vertexIndex[2]-1);
				uvIndices.push_back(uvIndex[0]-1);
				uvIndices.push_back(uvIndex[1]-1);
				uvIndices.push_back(uvIndex[2]-1);
				normalIndices.push_back(normalIndex[0]-1);
				normalIndices.push_back(normalIndex[1]-1);
				normalIndices.push_back(normalIndex[2]-1);
			}
			else if (strcmp(lineHeader, "o") == 0)
			{
				fscanf(file, "%s", &mesh->name);

			}

		}
		//for (size_t i = 0; i < vertexIndices.size(); i++)
		//{
		//	unsigned int vertexIndex = vertexIndices[i];
		//	vector3 vertex = temp_Vertices[vertexIndex - 1];
		//	mesh->vertices.push_back(vertex);
		//	mesh->indicesVertices.push_back(vertexIndex);
		//}

		mesh->vertices = temp_Vertices;
		mesh->indicesVertices = vertexIndices;
		/*for (size_t i = 0; i < uvIndices.size(); i++)
		{
			unsigned int uvIndex = uvIndices[i];
			vector2 uv = temp_UV[uvIndex - 1];
			mesh->uv.push_back(uv);
			mesh->indicesUV.push_back(uvIndex);
		}*/
		mesh->uv = temp_UV;
		mesh->indicesUV = uvIndices;
		//for (size_t i = 0; i < normalIndices.size(); i++)
		//{
		//	unsigned int normalIndex = normalIndices[i];
		//	vector3 normal = temp_Normals[normalIndex - 1];
		//	mesh->normals.push_back(normal);
		//	mesh->indicesNormals.push_back(normalIndex);
		//}

		mesh->normals = temp_Normals;
		mesh->indicesNormals = normalIndices;
		return mesh;
	}
}