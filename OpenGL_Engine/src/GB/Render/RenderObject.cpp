#include "gbpch.h"
#include "RenderObject.h"
#include "Buffer.h"
#include "Math.h"
#include "Camera.h"
#include "glad/glad.h"

namespace GB
{

	RenderObject::RenderObject(Material* mat,std::string name) :m_name(name), m_transform(), m_color(1.0f),material(mat)
	{
		if (mesh == nullptr) mesh = new Mesh();
	}
	RenderObject::~RenderObject()
	{

	}
	void RenderObject::UnBind()
	{
		m_vertexArray->UnBind();
	}
	/*
	@param vertices Representa al array de vertices que incluye el objeto
	@param size el tamaño en bytes de los vertices, normalmente es el numero de lineas * numero de componentes* sizeof(float)
	@param indices un array con los indices que hay por vertice
	@param count el numero de elementos de indices
	*/
	void RenderObject::Create(float* vertices, uint32_t size, uint32_t* indices, uint32_t count)
	{
		m_vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, size));

		BufferLayout layout = {
		  { EShaderDataType::Float3,"_Position"},
		  { EShaderDataType::Float2,"_TexCoord"}
		};

		vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, count));
		m_vertexArray->SetIndexBuffer(indexBuffer);
	}

	void RenderObject::Create(std::vector<glm::vec3>& vertices, std::vector<uint32_t>& verticesIndices)
	{
		m_vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create((float*)&vertices[0], 3 * vertices.size() * sizeof(float)));
		BufferLayout layout =
		{
			{ EShaderDataType::Float3,"_Position"}
		};

		vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(&verticesIndices[0], verticesIndices.size()));
		m_vertexArray->SetIndexBuffer(indexBuffer);
	}

	void RenderObject::Create(Mesh& newMesh)
	{
		mesh = &newMesh;
		m_vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<VertexBuffer> uvBuffer;
		vertexBuffer.reset(VertexBuffer::Create((float*)&newMesh.vertices[0], newMesh.vertices.size() * sizeof(vector3)));
		BufferLayout layout =
		{
			{EShaderDataType::Float3,"_Position"}

		};

		vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(&mesh->indicesVertices[0], mesh->indicesVertices.size()));
		m_vertexArray->SetIndexBuffer(indexBuffer);

	}

	void RenderObject::Render(int mode)
	{
		material->Bind();
		material->SetMat4("u_transform", m_transform.GetMat4());
		material->SetMat4("u_view", Camera::GetMain()->GetView());
		material->SetMat4("u_proj", Camera::GetMain()->GetProj());
		material->SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
		material->SetInt("u_Texture", 0);

		m_vertexArray->Bind();
		glDrawElements(mode, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

#pragma region Primitives


	Sprite::Sprite(Material* mat,uint32_t textID, const std::string name) : RenderObject(mat)
	{
		this->m_name = name;
		this->m_textureID = textID;
		float verticesPlane[]
		{//vertices           //uv
		  -0.5f, -0.5f,0.0f, 0.0f, 0.0f,
		   0.5f, -0.5f,0.0f, 1.0f, 0.0f,
		   0.5f, 0.5f,0.0f,  1.0f, 1.0f,
		  -0.5f, 0.5f,0.0f,  0.0f, 1.0f
		};

		uint32_t indicesPlane[]
		{
		  0,1,2,
		  2,3,0
		};
		this->Create(verticesPlane, sizeof(verticesPlane), indicesPlane, sizeof(indicesPlane) / sizeof(uint32_t));
	}
	Sprite::~Sprite()
	{

	}
	Cube::Cube(Material* mat, uint32_t textID, const std::string name) : RenderObject(mat)
	{
		this->m_name = name;
		this->m_textureID = textID;
		this->material = mat;
		float verticesCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,//0
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,//1
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//2
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,//3

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//4
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,//5
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,//6
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,//7

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//8
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,//9
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//10

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,//11
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,//12
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,//13

		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,//14
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,//15
		};
		uint32_t indiceCube[]
		{
		0,1,2,2,3,0,
		4,5,6,6,7,4,
		8,9,10,10,4,8,
		11,2,12,12,13,11,
		10,14,5,5,4,10,
		3,2,11,11,15,3
		};

		mesh = new Mesh();

		for (size_t i = 5; i <= 80; i += 5)
		{
			mesh->vertices.push_back(vector3(verticesCube[i - 5], verticesCube[i - 4], verticesCube[i - 3]));
			mesh->uv.push_back(vector2(verticesCube[i - 2], verticesCube[i - 1]));
		}
		unsigned int size = sizeof(indiceCube) / sizeof(uint32_t);
		std::copy(&indiceCube[0], &indiceCube[size], std::back_inserter(mesh->indicesVertices));
		this->mesh = mesh;
		Create(verticesCube, 5 * 16 * sizeof(float), indiceCube, 36);
	}
	Cube::~Cube()
	{
	}


	void Cube::Render(int mode)
	{
		material->Bind();
		material->SetMat4("u_transform", m_transform.GetMat4());
		material->SetMat4("u_view", Camera::GetMain()->GetView());
		material->SetMat4("u_proj", Camera::GetMain()->GetProj());
		material->SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
		material->SetInt("u_Texture", 0);

		m_vertexArray->Bind();
		glDrawElements(mode, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
#pragma endregion
	Line::Line(Material* mat, const vector2& origin, const vector2& destiny) : RenderObject(mat)
	{
		m_textureID = 0;
		m_name = "Line";
		m_color = color(0.0f, 1.0f, 0.0f, 1.0f);
		float temp[] = { origin.x,origin.y,0.0f,destiny.x,destiny.y,0.0f };

		m_vertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create((float*)&temp, 3 * 2 * sizeof(float)));

		BufferLayout layout = {
		  { EShaderDataType::Float3,"_Position"},
		};

		vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer;
		uint32_t temp1[2] = { 0,1 };
		indexBuffer.reset(IndexBuffer::Create(temp1, 2));
		m_vertexArray->SetIndexBuffer(indexBuffer);
	}
	void Line::Render(int mode)
	{
		material->Bind();
		material->SetMat4("u_transform", m_transform.GetMat4());
		material->SetMat4("u_view", Camera::GetMain()->GetView());
		material->SetMat4("u_proj", Camera::GetMain()->GetProj());
		material->SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);

		m_vertexArray->Bind();
		glDrawElements(GL_LINE_LOOP, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}
}