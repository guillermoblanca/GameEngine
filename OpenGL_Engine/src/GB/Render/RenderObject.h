#pragma once

#pragma region Includes
#include "GB\Core.h"

#include "Material.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include "GB\ComponentSystem\Transform.h"
#pragma endregion


namespace GB
{
	struct RenderData
	{
		RenderData(float& data, unsigned int indices, std::string path);
		VertexBuffer buffer;
		IndexBuffer indexbuffer;
	std::shared_ptr<Material*> mat;
	};

	
	class GBAPI IRender
	{
	public:
		virtual void Render() = 0;
	};
	class GBAPI Sprite :  public IRender
	{

	public:

		virtual void Render() override {};
	};


	class GBAPI RenderObject : IRender
	{
	public:

		RenderObject(const float *positions, unsigned int size, const unsigned int *data, unsigned int count, Material * mat);
		~RenderObject();
		void UnBind();
		virtual void Render()override;

		inline Material* GetMat() { return m_mat; }
		glm::vec4 m_color;
		Transform m_transform;
	protected:
		virtual void ParameterUpdate();
		VertexBuffer *m_vb;
		IndexBuffer m_ib;
		Material * m_mat;


	};
}