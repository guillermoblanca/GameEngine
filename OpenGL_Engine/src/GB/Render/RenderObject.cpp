#include "gbpch.h"
#include "RenderObject.h"
#include "glad\glad.h" 

#include "glad\glad.h" 
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Camera.h"
namespace GB
{

	RenderObject::RenderObject(const float *positions,unsigned int size, const unsigned int *data, unsigned int count, Material * mat) : 
		m_ib(data, count), m_mat(mat),m_transform(1.0f), m_color(1.0f)
	{

		m_vb = new VertexBuffer(positions,size);
		VertexArray m_va;
		VertexBufferLayout m_layout;

		m_layout.Push<float>(3);
		m_layout.Push<float>(2);
		m_va.AddBuffer(*m_vb, m_layout);



		m_ib.Bind();
		m_mat->Bind();
		/*glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(pos[0], pos[1], pos[2]));
		trans = glm::scale(trans, glm::vec3(pos[3], pos[4], pos[5]));
		m_mat->SetMat4("u_transform", trans);*/
	}
	RenderObject::~RenderObject()
	{
		delete m_mat;
		delete m_vb;
	}
	void RenderObject::UnBind()
	{
		m_ib.Unbind();
	}
	void RenderObject::Render()
	{
		m_mat->Bind();
		m_ib.Bind();
		ParameterUpdate();
		glDrawElements(GL_TRIANGLES, m_ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void RenderObject::ParameterUpdate()
	{
		m_mat->SetMat4("u_transform", m_transform);
		m_mat->SetMat4("u_view", Camera::GetView());
		m_mat->SetMat4("u_proj", Camera::GetProj());
		m_mat->SetVector4("u_Color", m_color.r,m_color.g,m_color.b,m_color.a);
	}

}