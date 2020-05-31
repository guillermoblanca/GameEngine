#pragma once
#include "GB/Math.h"
#include "GB/Core.h"

//for reader stream
//todo: create IOModule which will manage all this content
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
		std::string name;

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
		static Mesh* ReadMeshFromFile(const char* path);
	private:
	};
}