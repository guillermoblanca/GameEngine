#pragma once
#include "GB/Core.h"
#include "GB/Math.h"
namespace GB
{

	void ConvertRawData(const std::vector<vector3>& vertices,const std::vector<uint32_t>& indicesVertices,const std::vector<vector2>& uv,const std::vector<uint32_t>& indicesuv)
	{
		size_t verticescount = vertices.size(); //sets the number of rows

		std::vector<float> rawData;

		//raw data 3 vertices, 2uv
		for (size_t i = 0; i < verticescount; i++)
		{
			// sets 3 vertices
			//sets 2 uv

		}

	}
}