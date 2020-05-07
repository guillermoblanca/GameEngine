#include "gbpch.h"
#include "Renderer.h"
#include "imgui.h"
#include "Buffer.h"

#include "GB/Application.h"
#include "GB/Math.h"
#include "GB/Input.h"
#include "GB/Render/RenderCommand.h"

#include "GB/Utils/FileSystem.h"
namespace GB
{
	Renderer* Renderer::m_singleton = nullptr;
	vector2 values = { 0.5f,0.5f };

	void Renderer::BeginScene(Camera camera)
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);
	}

	Renderer::Renderer() : m_renderIndex(0), renderColor(0, 0.5f, 0.5f, 1.0f)
	{
		m_singleton = this;
	}

	Renderer::~Renderer()
	{
		for (RenderObject* render : m_renderObjects)
		{
			delete render;
		}

		for (Material* mat : m_materials)
		{
			delete mat;
		}
	}

	void Renderer::OnAttach()
	{
		GB_CORE_INFO("Initialized Render class");


		RenderCommand::AlphaMode(true);
		RenderCommand::DephtTest(true);

	}
	void Renderer::OnDetach()
	{
		for (int i = 0; i < m_textures.size(); i++) delete m_textures[i];
		for (int i = 0; i < m_renderObjects.size(); i++) delete m_renderObjects[i];
	}

	void Renderer::OnRender()
	{
		for (size_t i = 0; i < m_materials.size(); i++)
		{
			m_materials[i]->SetFloat("iTime", Time::GetTime());
			m_materials[i]->SetVector2("iResolution", values.x, values.y);
		}
		//Loop for renderOjects and setting different options
		for (int i = 0; i < m_renderObjects.size(); i++)
		{
			RenderObject* obj = m_renderObjects[i];
			Texture2D* texture = m_textures[Mathf::Clamp0(obj->m_textureID)];
			if (texture)
			{
				texture->Bind(0);
			}
			obj->Render((int)mode);
		}

	}
	void Renderer::PushObj(RenderObject * obj)
	{
		m_renderObjects.emplace(m_renderObjects.begin() + m_renderIndex, obj);
		m_renderIndex++;
	}
	void Renderer::PushOverLay(RenderObject * obj)
	{
		m_renderObjects.emplace_back(obj);
	}
	void Renderer::PopObj(RenderObject * obj)
	{
		auto it = std::find(m_renderObjects.begin(), m_renderObjects.end(), obj);
		if (it != m_renderObjects.end())
		{
			m_renderObjects.erase(it);
			m_renderIndex--;
		}
	}
	void Renderer::PopOverlay(RenderObject * obj)
	{
		auto it = std::find(m_renderObjects.begin(), m_renderObjects.end(), obj);
		if (it != m_renderObjects.end())
			m_renderObjects.erase(it);
	}
	void Renderer::SetRenderMode(ERenderMode mode)
	{
		this->mode = mode;
	}
	void Renderer::OnImguiRender()
	{
		static int random = 0;
		static bool useAlpha = true;
		static int i = 0;
		static float rot[] = { 0,0,0 };
		glm::vec3 position;
		glm::quat quat;
		glm::vec3 scale;
		glm::vec3 skew;
		glm::vec4 perspective;
		RenderObject* render = nullptr;
		ImGui::Begin("Render");
		ImGui::DragFloat2("iResolution", (float*)&values,0.01f,-1.0f,1.0f);
		if (ImGui::Button("Change Alpha mode")) { useAlpha = !useAlpha; RenderCommand::AlphaMode(useAlpha); }

		if (ImGui::CollapsingHeader("Materials"))
		{
			for (size_t i = 0; i < m_materials.size(); i++)
			{
				ImGui::Text("%s", m_materials[i]->GetPath().c_str());
				ImGui::Spacing();
				//ImGui::Text("Value: %s",m_materials[i]->SetFloat)

			}
		}

		if (ImGui::CollapsingHeader("Files in shader folder"))
		{
			static std::vector<std::string> files = FileParser::GetFilesInDirectory(*"Assets/Shader");

			for (size_t i = 0; i < files.size(); i++)
			{
				ImGui::Text("%s", files[i].c_str());
			}

		}

		if (ImGui::CollapsingHeader("Background Color"))
		{
			ImGui::ColorPicker4("Render Color", (float*)&renderColor);
		}
		if (ImGui::CollapsingHeader("All textures"))
		{
			for (int i = 0; i < m_textures.size(); i++)
				ImGui::Image((ImTextureID)m_textures[i]->GetID(), ImVec2(200, 200));

		}

		if (ImGui::Button("Add Plane"))
		{
			PushObj(new Sprite(m_materials[0], Mathf::Random(0, m_textures.size() - 1)));
		}
		ImGui::SameLine();
		if (ImGui::Button("Add Cube"))
		{
			PushObj(new Cube(m_materials[0], Mathf::Random(0, m_textures.size() - 1)));
		}
		if (ImGui::Button("Remove Last RenderObject") && !m_renderObjects.empty())
		{
			int index = m_renderObjects.size() - 1;
			PopObj(m_renderObjects[index]);
		}

		ImGui::DragInt("INDEX", &i, 1, 0, (int)m_renderObjects.size() - 1); ImGui::SameLine();
		ImGui::Text("%d", m_renderObjects.size());
		if (ImGui::TreeNode("RenderObject Info"))
		{
			for (int i = 0; i < m_renderObjects.size(); i++)
				if (ImGui::TreeNode((void*)(intptr_t)i, "%s", m_renderObjects[i]->m_name.c_str()))
				{
					RenderObjectImgui(render, i, scale, quat, position, skew, perspective, rot);
				}
			ImGui::TreePop();
		}
		ImGui::End();


	}
	void Renderer::RenderObjectImgui(GB::RenderObject*& render, int i, glm::vec3& scale, glm::quat& quat, glm::vec3& position, glm::vec3& skew, glm::vec4& perspective, float  rot[3])
	{
		render = m_renderObjects[i];
		glm::decompose(render->m_transform.GetMat4(), scale, quat, position, skew, perspective);
		glm::vec3 rotator = render->m_transform.rotation;
		ImGui::InputText("Name:", render->m_name.data(), 64);
		ImGui::DragFloat3("Position", (float*)&position, 0.1f);
		ImGui::DragFloat3("Rotation", rot, 0.1f);
		ImGui::DragFloat3("Scale", (float*)&scale, 0.1f);

		ImGui::Separator();
		ImGui::Text("Pos: %2f,%2f,%2f", position.x, position.y, position.z);
		ImGui::Text("Rotation: %2f,%2f,%2f", Mathf::ToDegrees(rotator.x), Mathf::ToDegrees(rotator.y), Mathf::ToDegrees(rotator.z));
		ImGui::Text("Scale: %2f,%2f,%2f", scale.x, scale.y, scale.z);
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Material"))
		{

		}
		if (ImGui::CollapsingHeader("Color properties", ImGuiTreeNodeFlags_Bullet))
		{
			ImGui::DragInt("Texture", &m_renderObjects[i]->m_textureID, 1, 0, m_textures.size() - 1);
			if (ImGui::Button("Texture Up")) m_renderObjects[i]->m_textureID = Mathf::Clamp<int>(m_renderObjects[i]->m_textureID + 1, 0, m_textures.size() - 1);
			ImGui::SameLine();
			if (ImGui::Button("Texture Down")) m_renderObjects[i]->m_textureID = Mathf::Clamp<int>(m_renderObjects[i]->m_textureID - 1, 0, m_textures.size() - 1);
			ImGui::ColorPicker4("Color", (float*)&render->m_color);
			ImGui::Image((ImTextureID)m_textures[render->m_textureID]->GetID(), ImVec2(200, 200));
		}

		if (render->mesh != nullptr) render->mesh->WindowProperties();

		render->m_transform.Translate(position);
		render->m_transform.Rotate(glm::vec3(glm::radians(rot[0]), glm::radians(rot[1]), glm::radians(rot[2])));
		render->m_transform.SetScale(scale);
		ImGui::TreePop();
	}
}