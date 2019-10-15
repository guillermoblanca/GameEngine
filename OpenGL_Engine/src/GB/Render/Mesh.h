#pragma once
#include "GB/Math.h"
#include "GB/Core.h"

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


		void WindowProperties();
	private:

	};
}