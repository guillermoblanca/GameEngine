#pragma once

#include "gbpch.h"
#include "GB\Core.h"
#include "glad\glad.h"
#define GB_FLOAT 0x1406
#define GB_UNSIGNED_INT 0x1405
#define GB_UNSIGNED_BYTE 0X1401
namespace GB
{

	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GB_FLOAT: return 4;
			case GB_UNSIGNED_INT: return 4;
			case GB_UNSIGNED_BYTE: return 1;
			}

			GB_CORE_ASSERT(false, "Type error");
			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout(): m_Stride(0){}
		~VertexBufferLayout();

		template<typename T>
		void Push(unsigned int count)
		{
			GB_CORE_ERROR("Vertex Buffer Layout: Push need a type definition");
			static_assert(false);
		}
		template<>
		void Push<float>(unsigned int count)
		{
			
			m_Elements.push_back({ GB_FLOAT,count,GL_FALSE });
			m_Stride += count *VertexBufferElement::GetSizeOfType(GB_FLOAT);
		}
		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_Elements.push_back({ GB_UNSIGNED_INT,count,GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GB_UNSIGNED_INT);

		}
		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_Elements.push_back({ GB_UNSIGNED_BYTE,count,GL_TRUE });
			m_Stride += count *VertexBufferElement::GetSizeOfType(GB_UNSIGNED_BYTE);

		}

		inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
		inline unsigned int GetStride() const& { return m_Stride; }
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};
}