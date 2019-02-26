#pragma once

#include "gbpch.h"
#include "GB/Core.h"
#include "Material.h"

namespace GB
{

	class GBAPI Render
	{
	public:
		void Init();
		void Draw();
	private:
		unsigned int ibo;
		unsigned int vao;
		Material material;;
	};



}
