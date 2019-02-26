#pragma once

#include "GB\Core.h"

namespace GB
{

	class VertexBuffer
	{
		public:

			VertexBuffer(const void* data, unsigned int size);
			~VertexBuffer();
			void Bind() const;
			void Unbind() const;
		private:
			unsigned int m_RendererID;

	};

	
}
