#include "gbpch.h"
#include "RenderObject.h"
#include "Buffer.h"
#include "Math.h"
#include "Camera.h"
#include "glad/glad.h"

namespace GB
{

	RenderObject::RenderObject(std::string name) :m_name(name), m_transform(), m_color(1.0f)
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

	void RenderObject::Render(Material& material, int mode)
	{
		material.Bind();
		material.SetMat4("u_transform", m_transform.GetMat4());
		material.SetMat4("u_view", Camera::GetMain()->GetView());
		material.SetMat4("u_proj", Camera::GetMain()->GetProj());
		material.SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
		material.SetInt("u_Texture", 0);

		m_vertexArray->Bind();
		glDrawElements(mode, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

#pragma region Primitives


	Sprite::Sprite(uint32_t textID, const std::string name)
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
	Cube::Cube(uint32_t textID, const std::string name)
	{
		this->m_name = name;
		this->m_textureID = textID;


		uint32_t indiceCube[]
		{
		0,1,2,2,3,0,
		4,5,6,6,7,4,
		8,9,10,10,4,8,
		11,2,12,12,13,11,
		10,14,5,5,4,10,
		3,2,11,11,15,3
		};

		int count = sizeof(indiceCube) / sizeof(indiceCube[0]);

		std::vector<vector3> vertices;
		std::vector<vector2> uv;
		std::vector<uint32_t> vertindices(indiceCube,indiceCube+count);

		vertices.push_back({  -0.5f, -0.5f, -0.5f });
		vertices.push_back({   0.5f, -0.5f, -0.5f });
		vertices.push_back({   0.5f,  0.5f, -0.5f });
		vertices.push_back({  -0.5f,  0.5f, -0.5f });
		vertices.push_back({  -0.5f, -0.5f,  0.5f });
		vertices.push_back({   0.5f, -0.5f,  0.5f });
		vertices.push_back({   0.5f,  0.5f,  0.5f });
		vertices.push_back({  -0.5f,  0.5f,  0.5f });
		vertices.push_back({  -0.5f,  0.5f,  0.5f });
		vertices.push_back({  -0.5f,  0.5f, -0.5f });
		vertices.push_back({  -0.5f, -0.5f, -0.5f });
		vertices.push_back({   0.5f,  0.5f,  0.5f });
		vertices.push_back({   0.5f, -0.5f, -0.5f });
		vertices.push_back({   0.5f, -0.5f,  0.5f });
		vertices.push_back({   0.5f, -0.5f, -0.5f });
		vertices.push_back({  -0.5f,  0.5f,  0.5f });

		uv.push_back({0.0f, 0.0f});
		uv.push_back({1.0f, 0.0f});
		uv.push_back({1.0f, 1.0f});
		uv.push_back({0.0f, 1.0f});
		uv.push_back({0.0f, 0.0f});
		uv.push_back({1.0f, 0.0f});
		uv.push_back({1.0f, 1.0f});
		uv.push_back({0.0f, 1.0f});
		uv.push_back({1.0f, 0.0f});
		uv.push_back({1.0f, 1.0f});
		uv.push_back({0.0f, 1.0f});
		uv.push_back({1.0f, 0.0f});
		uv.push_back({0.0f, 1.0f});
		uv.push_back({0.0f, 0.0f});
		uv.push_back({1.0f, 1.0f});
		uv.push_back({0.0f, 0.0f});
		mesh = new Mesh();
		this->mesh->vertices = vertices;
		this->mesh->uv = uv;
		this->mesh->indicesVertices = vertindices;
		Create(vertices, vertindices);
	}
	Cube::~Cube()
	{
	}
	void Cube::Render(Material & material, int mode)
	{
		material.Bind();
		material.SetMat4("u_transform", m_transform.GetMat4());
		material.SetMat4("u_view", Camera::GetMain()->GetView());
		material.SetMat4("u_proj", Camera::GetMain()->GetProj());
		material.SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
		material.SetInt("u_Texture", 0);

		m_vertexArray->Bind();
		glDrawElements(mode, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
#pragma endregion
	Line::Line(const vector2 & origin, const vector2 & destiny)
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
	void Line::Render(Material & material, int mode)
	{
		material.Bind();
		material.SetMat4("u_transform", m_transform.GetMat4());
		material.SetMat4("u_view", Camera::GetMain()->GetView());
		material.SetMat4("u_proj", Camera::GetMain()->GetProj());
		material.SetVector4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);

		m_vertexArray->Bind();
		glDrawElements(GL_LINE_LOOP, m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}
}