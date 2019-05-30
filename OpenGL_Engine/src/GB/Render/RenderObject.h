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
		virtual void Render(Material& material, int mode = 4) = 0;
	};
	class GBAPI Sprite :  public IRender
	{

	public:
		Sprite(Texture text);
		~Sprite();

		virtual void Render(Material& material, int mode = 4) override;
		Transform m_transform;
		glm::vec4 m_color;
		Texture* m_texture;

	protected:
		VertexBuffer *m_vb;
		IndexBuffer m_ib;
	};


	class GBAPI RenderObject : IRender
	{
	public:

		RenderObject();
		~RenderObject();
		void UnBind();
		virtual void Render(Material& material, int mode=4)override;
		virtual void Create(const float *positions, unsigned int size, const unsigned int *data, unsigned int count);

		unsigned int m_textureID;
		glm::vec4 m_color;
		Transform m_transform;
	protected:
		VertexBuffer *m_vb;
		IndexBuffer m_ib;


	};
}