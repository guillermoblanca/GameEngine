#include "gbpch.h"
#include "RenderObject.h"
#include "glad\glad.h" 

#include "glad\glad.h" 
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Math.h"
#include "Camera.h"
namespace GB
{
	RenderObject::RenderObject() :m_ib(),m_transform(),m_color(1.0f)
	{
	}
	RenderObject::~RenderObject()
	{
		
		delete m_vb;
	}
	void RenderObject::UnBind()
	{
		m_ib.Unbind();
	}
	void RenderObject::Render(Material& material,int mode)
	{
		material.Bind();
		material.SetMat4("u_transform", m_transform.GetMat4());
		material.SetMat4("u_view", Camera::GetView());
		material.SetMat4("u_proj", Camera::GetProj());
		material.SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
		material.SetInt("u_Texture", 0);

		m_ib.Bind();
		glDrawElements(mode, m_ib.GetCount(), GL_UNSIGNED_INT, nullptr);
		m_ib.Unbind();
	}
	void RenderObject::Create(const float * positions, unsigned int size, const unsigned int * data, unsigned int count)
	{
		m_ib.Create(data, count);
		m_vb = new VertexBuffer(positions, size);
		VertexArray m_va;
		VertexBufferLayout m_layout;
		m_layout.Push<float>(3);
		m_layout.Push<float>(2);
		m_va.AddBuffer(*m_vb, m_layout);

		m_ib.Bind();
	}
	Sprite::Sprite(Texture tex): m_ib(),m_vb(nullptr),m_texture(&tex)
	{
		const float positions[]
		{//vertices           //uv
			-0.5f,-0.5f,0.0f, 0.0f, 0.0f,
			 0.5f,-0.5f,0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f,0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f,0.0f, 0.0f, 1.0f
		};

		unsigned int indices[]
		{
			0,1,2,
			2,3,0
		};

		m_vb = new VertexBuffer(positions, 5*4*sizeof(float));
		VertexArray m_va;
		VertexBufferLayout m_layout;
		m_layout.Push<float>(3);
		m_layout.Push<float>(2);
		m_va.AddBuffer(*m_vb, m_layout);
		
		m_ib.Bind();
	}
	Sprite::~Sprite()
	{
		m_ib.Unbind();
	}
	void Sprite::Render(Material & material, int mode)
	{
		material.Bind();
		material.SetMat4("u_transform", m_transform.GetMat4());
		material.SetMat4("u_view", Camera::GetView());
		material.SetMat4("u_proj", Camera::GetProj());
		material.SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
		m_texture->Bind(0);
		material.SetInt("u_Texture", 0);

		m_ib.Bind();
		glDrawElements(mode, m_ib.GetCount(), GL_UNSIGNED_INT, nullptr);
		m_ib.Unbind();
	}
}