#pragma once

#pragma region Includes
#include "GB\Core.h"

#include "Material.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

//transformation
#include "glm/glm.hpp"
#include "glm\gtx\transform.hpp"
#pragma endregion


namespace GB
{
	struct RenderData
	{
		VertexBuffer buffer;
		IndexBuffer indexbuffer;
	std::shared_ptr<Material*> mat;
	};

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform()
		{
			position = glm::vec3(0.0f);
			rotation = glm::vec3(0.0f);
			scale = glm::vec3(1.0f);
		}
		void Translate(glm::vec3 pos)
		{
			//todo: find if works
			auto dir = pos - position;

			position += dir;
		}
		void SetScale(glm::vec3 scl)
		{
			scale = scl;
		}
		void Rotate(glm::vec3 rot)
		{
			rotation = rot;
		}
		inline glm::mat4 GetMat4() 
		{
			glm::mat4 mat(1.0f);
			mat = glm::translate(mat, position);
			mat = glm::rotate(mat, rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));
			mat = glm::rotate(mat, rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));
			mat = glm::rotate(mat, rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));

			mat = glm::scale(mat, scale);

			return mat;
		}

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