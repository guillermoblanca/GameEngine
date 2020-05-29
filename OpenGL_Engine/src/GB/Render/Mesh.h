#pragma once
#include "GB/Math.h"
#include "GB/Core.h"

//for reader stream
//todo: create IOModule which will manage all this content
#include <fstream>
#include <regex>
namespace GB
{
	class Mesh
	{
	public:

		Mesh();
		std::vector<vector3> vertices;
		std::vector<vector3> normals;
		std::vector<vector2> uv;

		std::vector<uint32_t> indicesVertices;
		std::vector<uint32_t> indicesNormals;
		std::vector<uint32_t> indicesUV;

		std::vector<std::string> debugInfo;
		char name[255];

		void WindowProperties();
		static Mesh* Create(const char* path);
	private:

	};

	class MeshReader
	{
	public:

		static bool ConvertFileToMesh(const char* path, Mesh& mesh)
		{
			std::string line;
			std::ifstream streamFile;
			streamFile.open(path);

			if (!streamFile.is_open())
			{
				GB_CORE_ERROR("File cannot be open: {0}", path);
				return false;
			}

			while (std::getline(streamFile, line)) 
			{
				//en caso de ser una linea vacia deberia hacer un continue

				if (line.empty())continue;

				if (line.find('#') !=std::string::npos)
				{
					mesh.debugInfo.push_back(line);
				}
				else if (line.find('v') != std::string::npos)
				{
					vector3 vertex;
					std::stringstream ss(line);
					std::string temp;
					ss >> temp >> vertex.x >> vertex.y >> vertex.z;

					if (temp == "v") //vertices
					{
					mesh.vertices.push_back(vertex);
					}
					else if(temp == "vn")//normals
					{
						mesh.normals.push_back(vertex);
					}
					else if (temp == "vt") //texturecoord
					{
						mesh.uv.push_back(vertex);
					}
				}
				
			}

			//close stream 
			streamFile.close();
			return true;

		}

		static Mesh* ReadMeshFromFile(const char* path)
		{
			Mesh* mesh = new Mesh();

			std::vector<vector3> temp_Vertices;
			std::vector<vector2> temp_UV;
			std::vector<vector3> temp_Normals;
			std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;

			FILE* file = fopen(path, "r");

			if (file == NULL)
			{
				GB_CORE_ERROR("ERROR READING FILE OBJ: {0}", path);
				return nullptr;
			}
			bool active = true;
			char lineHeader[128];
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
				else if (strcmp(lineHeader, "f") == 0)
				{
					uint32_t vertexIndex[3], uvIndex[3], normalIndex[3];
					int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					if (matches != 9)
					{
						GB_CORE_ERROR("File can't be read!");

						return nullptr;
					}
					vertexIndices.push_back(vertexIndex[0] - 1);
					vertexIndices.push_back(vertexIndex[1] - 1);
					vertexIndices.push_back(vertexIndex[2] - 1);
					uvIndices.push_back(uvIndex[0] - 1);
					uvIndices.push_back(uvIndex[1] - 1);
					uvIndices.push_back(uvIndex[2] - 1);
					normalIndices.push_back(normalIndex[0] - 1);
					normalIndices.push_back(normalIndex[1] - 1);
					normalIndices.push_back(normalIndex[2] - 1);
				}
				else if (strcmp(lineHeader, "o") == 0)
				{
					fscanf(file, "%s", &mesh->name);
				}

			}

			mesh->vertices = temp_Vertices;
			mesh->indicesVertices = vertexIndices;
			mesh->indicesUV = uvIndices;
			mesh->uv = temp_UV;

			mesh->indicesNormals = normalIndices;
			mesh->normals = temp_Normals;
			return mesh;
		}
	private:
	};
}